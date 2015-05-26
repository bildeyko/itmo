/**
 * Created by ASUS on 25.05.2015.
 */
window.addEventListener("load", function() {
    var canvas, context, painting;
    var length, xC, yC;
    var result;

    function init() {
        result = document.getElementById("canvas_form:check_result");
        canvas = document.getElementById("paintingCanvas");
        if (canvas == null) return;

        context = canvas.getContext("2d");
        if (context == null) return;

        painting = false;

        xC = context.canvas.width/2;
        yC = context.canvas.height/2;
        length = (context.canvas.width/2 - 20)/2;

        context.fillStyle = "#FFC799";
        context.rect(xC, yC, length, length*2);
        context.arc(xC, yC, length, Math.PI/2, Math.PI);
        context.fill();
        context.beginPath();
        context.moveTo(xC, yC-2*length);
        context.lineTo(xC+length, yC);
        context.lineTo(xC, yC);
        context.closePath();
        //context.stroke();
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
        context.fillText("Y", context.canvas.width/2 + 7, 15);

        context.moveTo(0,context.canvas.height/2);
        context.lineTo(context.canvas.width,context.canvas.height/2);
        context.lineTo(context.canvas.width - 10,context.canvas.height/2 + 5);
        context.moveTo(context.canvas.width,context.canvas.height/2);
        context.lineTo(context.canvas.width - 10,context.canvas.height/2 - 5);
        context.fillText("X", context.canvas.width - 15, context.canvas.height/2 - 7);
        context.closePath();
        context.stroke();

        //console.log(xC)
        //console.log(yC)
        //console.log(length)
    }

    init();
    var now = new Date();
    document.getElementById('clock').innerHTML = now;

    canvas.addEventListener("click", function(e) {
        var evt = e || window.event;
        var posX = evt.offsetX?(evt.offsetX):evt.pageX-canvas.offsetLeft;
        var posY = evt.offsetY?(evt.offsetY):evt.pageY-canvas.offsetTop;
        posX = posX - context.canvas.width/2;
        posY = -(posY - context.canvas.height/2);

        var r = document.getElementById('canvas_form:canvas_r').value;
        var normR = (length*2)/r;
        posX = (posX/normR).toFixed(2);
        posY = (posY/normR).toFixed(2);
        console.log(posX);
        console.log(posY);
        console.log(normR);

        document.getElementById('canvas_form:canvas_x').value = posX;
        //console.log(e.clientX);
        document.getElementById('canvas_form:canvas_y').value = posY;
        //document.getElementById('canvas_form:canvas_r').value = 5.0;
        document.getElementById('canvas_form:check_canvas').click();
    }, false);

    result.addEventListener("change", function(e) {
        console.log("CHANGE");
    }, false);

   function showResult(elem) {
        console.log("CHANGE!!!");
    }

}, false);

var timerId = setInterval(function() {
    var now = new Date();
    document.getElementById('clock').innerHTML = now;
}, 8000);