/**
 * Created by ASUS on 25.05.2015.
 */
var canvas, context, painting;
var length, xC, yC;
var result;


window.addEventListener("load", function() {

    function init() {
        result = document.getElementById("canvas_form:check_result");
        canvas = document.getElementById("paintingCanvas");
        if (canvas == null) return;

        context = canvas.getContext("2d");
        if (context == null) return;

        painting = false;

        drawGraph();
    }

    init();
    drawPoints();
    var now = new Date();
    document.getElementById('clock').innerHTML = now;

    canvas.addEventListener("click", function(e) {
        var evt = e || window.event;
        //var posX = evt.offsetX?(evt.offsetX):evt.pageX-canvas.offsetLeft;
        //var posY = evt.offsetY?(evt.offsetY):evt.pageY-canvas.offsetTop;
        var posX = evt.offsetX === undefined ? evt.layerX-canvas.offsetLeft : evt.offsetX;
        var posY = evt.offsetY === undefined ? evt.layerY-canvas.offsetTop : evt.offsetY;
        posX = posX - context.canvas.width/2;
        posY = -(posY - context.canvas.height/2);

        var r = document.getElementById('canvas_form:canvas_r').value;
        var normR = (length*2)/r;
        posX = (posX/normR).toFixed(2);
        posY = (posY/normR).toFixed(2);
        //console.log(posX);
        //console.log(posY);
        //console.log(normR);

        document.getElementById('canvas_form:canvas_x').value = posX;
        //console.log(e.clientX);
        document.getElementById('canvas_form:canvas_y').value = posY;
        //document.getElementById('canvas_form:canvas_r').value = 5.0;
        document.getElementById('canvas_form:check_canvas').click();
    }, false);

    /*result.addEventListener("change", function(e) {
        console.log("CHANGE");
    }, false);

   function showResult(elem) {
        console.log("CHANGE!!!");
    }*/

}, false);

function drawPoint(r,x,y,res) {
    //var rr = parseInt(document.getElementById('canvas_form:canvas_r').value);
    if(res) context.fillStyle = "#0F0";
    else context.fillStyle="#F00";
    var normR = (length*2)/r;
   // realX = xC+x*length/2;
    //realY = yC-y*length/2;
    realX = xC+x*normR;
    realY = yC-y*normR;
   // console.log("Real coord");
   // console.log(realX);
   // console.log(realY);
    context.beginPath();
    context.arc(realX, realY, 2, 0, 2*Math.PI);
    context.closePath();
    context.fill();
}

function drawPoints() {
    var table = document.getElementById("resTable");
    for (var i=1; i< table.rows.length; i++) {
        //if (table.rows.item.length > 1) {
        var cells = table.rows.item(i).cells;
        if (cells.length > 1) {
            x = parseFloat(cells.item(1).textContent);
            y = parseFloat(cells.item(2).textContent);
            r = parseFloat(document.getElementById('canvas_form:canvas_r').value);
            res = false;
            if (x >= 0) {
                if (y >= 0 && y <= (r - 2 * x)) {
                    res = true;
                }
                if (y <= 0 && y >= -r && x <= r / 2) {
                    res = true;
                }
            } else {
                radius = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
                if (y <= 0 && radius <= r / 2) {
                    res = true;
                }
            }
            drawPoint(r, x, y, res);
        }
       // }
    }
}

var timerId = setInterval(function() {
    var now = new Date();
    document.getElementById('clock').innerHTML = now;
}, 8000);

function checklistener(data) {

    if (data.status == "success") {
        //console.log("RESPONSE: "+data.responseText);
        res = document.getElementById('canvas_form:check_result').value;
        //console.log("RES: "+res);
        x = document.getElementById('canvas_form:canvas_x').value;
        y = document.getElementById('canvas_form:canvas_y').value;
        r = document.getElementById('canvas_form:canvas_r').value;
        if (res === "true")
            drawPoint(r, x, y, true);
        if (res === "false")
            drawPoint(r, x, y, false);
    }
}

function rChangeLinstener() {
    console.log("RRRRRRR: ");
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawGraph();
    drawPoints();
}

function drawGraph(){
    xC = context.canvas.width/2;
    yC = context.canvas.height/2;
    length = (context.canvas.width/2 - 20)/2;

    context.fillStyle = "#FFC799";
    context.beginPath();
    context.rect(xC, yC, length, length*2);
    context.arc(xC, yC, length, Math.PI/2, Math.PI);
    context.closePath();
    context.fill();
    context.beginPath();
    context.moveTo(xC, yC-2*length);
    context.lineTo(xC+length, yC);
    context.lineTo(xC, yC);
    context.closePath();
    context.fill();

    context.fillStyle = "#000";
    context.strokeStyle = "#000";
    context.lineWidth = 2;
    context.font = "15px Helvetica";
    context.beginPath();
    context.moveTo(context.canvas.width/2,context.canvas.height*2);
    context.lineTo(context.canvas.width/2,0);
    context.lineTo(context.canvas.width/2 + 5,10);
    context.moveTo(context.canvas.width/2,0);
    context.lineTo(context.canvas.width/2 - 5,10);
    context.closePath();
    context.stroke();


    context.beginPath();
    context.moveTo(0,context.canvas.height/2);
    context.lineTo(context.canvas.width,context.canvas.height/2);
    context.lineTo(context.canvas.width - 10,context.canvas.height/2 + 5);
    context.moveTo(context.canvas.width,context.canvas.height/2);
    context.lineTo(context.canvas.width - 10,context.canvas.height/2 - 5);
    context.closePath();
    context.stroke();
    context.fillText("X", context.canvas.width - 15, context.canvas.height/2 - 7);
    context.fillText("Y", context.canvas.width/2 + 7, 15);
}