<?php
	$time_start = microtime();
	$xVals = $_GET["xVals"];
	$yVal = (int) $_GET["yVal"];
	$rVals = $_GET["rVals"];

	if($yVal<-5 || $yVal>3 ) 
	{
		page(NULL, NULL, "Неверное значение y");
		exit;
	}

	$tbl = "<table>";
	foreach ($rVals as $r){
		$r = (int)$r;
		$tbl = $tbl."<tr><th colspan='2'>R =".$r."</th></tr>";
		if($r>5 || $r<1) {
			page(NULL, NULL, "Неверное значение r");
			exit;
		}
		foreach ($xVals as $x){
			if($x>2 || $x<-2) {
				page(NULL, NULL, "Неверное значение x");
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
	page($tbl, number_format($time, 6, '.',''), NULL);

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

	function page($table, $time, $error)
	{
		$result = '<html>
				<head>
					<meta charset="utf-8"> 
					<title>Лабораторная 6</title>

					<style type="text/css">
						html, body {
							height: 100%;
							padding: 0px;
							margin: 0px;
							font-family: Arial, "Helvetica CY", "Nimbus Sans L", sans-serif;	
							font-size: 14pt;
							background: #F3F3F3;			
						}

						div, img {
							/*border: 1px solid black;*/
						}

						#header {
							padding: 10px;
							background: #61D89F;
						}

						#header p {
							margin-top: 0px;
							margin-bottom: 0px;
							font-family: fantasy;
							font-size: 15pt;
							color: #363636;	
						}

						#wrapper {
							position: relative;
							height: 100%;
							width: 50%;
							min-width: 800px;
							margin: 0px auto ;
							background: #FFF;
						}

						.cell_point {
							background: #ddd;
						}

						.cell_res_good {
							background: #D2F3AA;
						}

						.cell_res_bad {
							background: #F3B5AA;
						}

						#center_container div {
							padding: 10px;
						}

						table {
							width: 200px;
							border-spacing: 0px;
							border-collapse: collapse;
						}

						td {
							padding: 5px;
							height: 20px;
							text-align: center;
							border: 1px solid #ddd;
						}

						#table_wrapper {
							max-height: 500px;
							width: 230px;
							overflow: auto;
						}

						.inline {
							display: inline-block;
							vertical-align:top;
						}

					</style>
				</head>
				<body>

					<div id="wrapper">
						<div id="header">
							<p>Бильдейко Николай Александрович</p>
							<p>студент группы 2101</p>
							<p>вариант 1101</p>
						</div>
						<div id="center_container">
							<div id="img_container" class="inline">
								<img src="img/areas.png" alt="альтернативный текст">
							</div>
							<div id="result_wrapper" class="inline">';
		if(is_null($error)) {
			$result = $result.'<p>Результаты проверки:</p>
								<div id="table_wrapper">'.$table.'</div>
								<p>Время работы скрипта: '.$time.' сек.</p>
								<p>Текущее время: '.date("d-m-Y H:i:s").'</p>';
		} else {
			$result = $result.'<p>Ошибка:</p>
								<p>'.$error.'</p>';		
		}
		$result = $result.'</div>
						</div>	
					</div>
				</body>
			</html>';

		echo $result;
	}
?>