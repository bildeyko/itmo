<%@ page import="java.util.Vector" %>
<%@ page import="lab7.Mark" %>
<%@ page import="java.util.Iterator" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <meta charset="utf-8">
  <title>Lab 8</title>
  <link rel="stylesheet" type="text/css" href="css/style.css"/>
  <script src="js/WebForm.js"></script>
</head>
<body>
  <div id="wrapper">
    <div id="header">
      <p>Nikolay Bildeyko</p>
      <p>group 2101</p>
      <p>variant 1147</p>
    </div>
    <div id="center_container">
      <div id="img_container" class="inline">
        <img id="graph_img" src="img/areas.png" onclick="imageClickHandler(event)">
        <div id="error_box"></div>
      </div>
      <div id="main_container" class="inline">
        <form id="input_form">
          <label>X</label>
          <br>
          <select name="xVal" onchange="changeXHandler()">
            <option value="-2"/>-2</option>
            <option value="-1.5"/>-1.5</option>
            <option value="-1"/>-1</option>
            <option value="-0.5"/>-0.5</option>
            <option value="0"/>0</option>
            <option value="0.5"/>0.5</option>
            <option value="1"/>1</option>
            <option value="1.5"/>1.5</option>
            <option value="2"/>2</option>
          </select>
          <br>
          <label>Y</label>
          <br>
          <input type="text" placeholder="-5...3" name="yVal" onblur="blurYHandler()"/>
          <br>
          <label>R</label>
          <br>
          <label><input class="rCheckbox" type="checkbox" name="rVal" onchange="checkedHandler(event)" value="1"/>1</label>
          <label><input class="rCheckbox" type="checkbox" name="rVal" onchange="checkedHandler(event)" value="2"/>2</label>
          <label><input class="rCheckbox" type="checkbox" name="rVal" onchange="checkedHandler(event)" value="3"/>3</label>
          <label><input class="rCheckbox" type="checkbox" name="rVal" onchange="checkedHandler(event)" value="4"/>4</label>
          <label><input class="rCheckbox" type="checkbox" name="rVal" onchange="checkedHandler(event)" value="5"/>5</label>
          <br>
          <label>Point to check: </label>
          <br>
          <span id="pointToCheck"></span>
          <br>
        </form>
        <button onclick="sendGlobalToServer()" value="Check point">Check point</button>
      </div>
      <%
        Vector<Mark> points = (Vector<Mark>)session.getAttribute("Points");
        if(points != null) {
      %>
      <div id="table_wrapper" class="inline">
        <p>Previous checks:</p>
        <table>
          <%
              Iterator it = points.iterator();
              while(it.hasNext()) {
                Mark point = (Mark)it.next();
          %>
          <tr><th colspan='2'>R = <%= point.r %></th></tr>
            <%  if(!point.status) { %>
                <tr><td class='cell_point'>( <%= point.x %>; <%= point.y %>)</td><td class='cell_res_bad'>Doesn't belong</td></tr>
            <%  } else { %>
                <tr><td class='cell_point'>( <%= point.x %>; <%= point.y %>)</td><td class='cell_res_good'>Belongs</td></tr>
            <%
                }
              }
          %>
      </div>
      <%
        }
      %>
    </div>
  </div>
</body>
</html>
