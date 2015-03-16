<?php
	$time_start = microtime();
	$xVals = $_GET["xVals"];
	$yVal =  $_GET["yVal"];
	$rVals = $_GET["rVals"];

	if(is_null($rVals) || is_null($xVals) || is_null($yVal))
	{
		indexPage();
	} else {
		if(!is_numeric($yVal) || $yVal<-5 || $yVal>3 ) 
		{
			resultPage(NULL, NULL, "Неверное значение y");
			exit;
		}

		$tbl = "<table>";
		foreach ($rVals as $r){
			$r = (int)$r;
			$tbl = $tbl."<tr><th colspan='2'>R =".$r."</th></tr>";
			if(!is_numeric($r) || $r>5 || $r<1) {
				resultPage(NULL, NULL, "Неверное значение r");
				exit;
			}
			foreach ($xVals as $x){
				if(!is_numeric($x) || $x>2 || $x<-2) {
					resultPage(NULL, NULL, "Неверное значение x");
					exit;
				}
				if(checkFigure($x, $yVal, $r))
					$tbl = $tbl."<tr><td class='cell_point'>(".$x."; ".$yVal.")</td><td class='cell_res_good'>Попадает</td></tr>";
				else
					$tbl = $tbl."<tr><td class='cell_point'>(".$x."; ".$yVal.")</td><td class='cell_res_bad'>Не попадает</td></tr>";
			}
		}
		$tbl = $tbl."</table>";

		$time_end = microtime();
		$time = $time_end - $time_start;
		resultPage($tbl, number_format($time, 6, '.',''), NULL);
	}

	function checkFigure($x, $y, $r)
	{
		if($x>0) 
		{
			if($y>0) {
				if($x+$y <= $r)
					return true;
				else
					return false;
			} else
				return false;
		} else {
			if($y>0) {
				if(pow($x, 2)+pow($y, 2) <= pow($r, 2)) 
					return true;
				else
					return false;
			} else {
				if($x>=(-$r/2) && $y>=(-$r)) 
					return true;
				else
					return false;
			}
		}
	}

	function indexPage()
	{
		$body = '<div id="main_container" class="inline">
					<form id="input_form" action="index.php" method="GET">
						<label>X</label>
						<br>
						<label><input type="checkbox" name="xVals[]" value="-2"/>-2</label>
						<label><input type="checkbox" name="xVals[]" value="-1.5"/>-1.5</label>
						<label><input type="checkbox" name="xVals[]" value="-1"/>-1</label>
						<label><input type="checkbox" name="xVals[]" value="-0.5"/>-0.5</label>
						<label><input type="checkbox" name="xVals[]" value="0"/>0</label>
						<label><input type="checkbox" name="xVals[]" value="0.5"/>0.5</label>
						<label><input type="checkbox" name="xVals[]" value="1"/>1</label>
						<label><input type="checkbox" name="xVals[]" value="1.5"/>1.5</label>
						<label><input type="checkbox" name="xVals[]" value="2"/>2</label>
						<br>
						<label>Y</label>
						<br>
						<input type="text" placeholder="-5...3" name="yVal"/>
						<br>
						<label>R</label>
						<br>
						<label><input type="checkbox" name="rVals[]" value="1"/>1</label>
						<label><input type="checkbox" name="rVals[]" value="2"/>2</label>
						<label><input type="checkbox" name="rVals[]" value="3"/>3</label>
						<label><input type="checkbox" name="rVals[]" value="4"/>4</label>
						<label><input type="checkbox" name="rVals[]" value="5"/>5</label>
						<br>
						<input type="submit" value="Проверить"/>
					</form>
				</div>';
		$tpl = file_get_contents('template.html');
		$tpl = str_replace('{body}', $body, $tpl);
		echo $tpl;
	}

	function resultPage($table, $time, $error)
	{
		$body = '<div id="result_wrapper" class="inline">';

		if(is_null($error)) {
			$body = $body.'<p>Результаты:</p>
								<div id="table_wrapper">'.$table.'</div>
								<p>Время работы скрипта: '.$time.' сек.</p>
								<p>Текущее время: '.date("d-m-Y H:i:s").'</p>';
		} else {
			$body = $body.'<p>Ошибка:</p>
								<p>'.$error.'</p>';		
		}

		$body = $body.'<form id="input_form" action="index.php" method="GET">
							<input type="submit" value="Новая проверка"/>
						</form>
						</div>
						</div>	
					</div>
				</body>
			</html>';

		$tpl = file_get_contents('template.html');
		$tpl = str_replace('{body}', $body, $tpl);
		echo $tpl;
	}
?>