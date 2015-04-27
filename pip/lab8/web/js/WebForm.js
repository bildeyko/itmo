var globalPoint = {
    x: null,
    y: null,
    r: null
}
window.onload = function(){
    globalPoint.x = parseFloat(document.forms["input_form"]["xVal"].value);
}

function validateForm() {
    if ((checkX() && checkY() && checkR()) ||
        (globalPoint.x != null && globalPoint.y != null && globalPoint.r != null))
        return true;
    return false;
}

function getCheckboxValue(group) {
    console.log(group);
    for (var i=0, iLen=group.length; i<iLen; i++) {
        if (group[i].checked) {
            return group[i].value;
        }
    }
    return '';
}

function sendGlobalToServer() {
    if(validateForm()) {
        var method = "post";
        var path = "/lab8_Web/check";
        var form = document.createElement("form");
        form.setAttribute("method", method);
        form.setAttribute("action", path);
        var params = {
            "xVal": globalPoint.x,
            "yVal": globalPoint.y,
            "rVal": globalPoint.r
        };
        for (var key in params) {
            if (params.hasOwnProperty(key)) {
                var hiddenField = document.createElement("input");
                hiddenField.setAttribute("type", "hidden");
                hiddenField.setAttribute("name", key);
                hiddenField.setAttribute("value", params[key]);

                form.appendChild(hiddenField);
            }
        }

        document.body.appendChild(form);
        form.submit();
    }
}

function checkX() {
    var x = document.forms["input_form"]["xVal"].value;
    if (x == "") {
        document.getElementById("error_box").innerHTML = "Select the X value";
        return false;
    }
    return true;
}

function changeXHandler() {
    var x = document.forms["input_form"]["xVal"].value;
    if(checkX())
    {
        globalPoint.x = parseFloat(x);
        showGlobalPoint();
    }
}

function checkY() {
    var y = document.forms["input_form"]["yVal"].value;
    if (isNaN(y) || y > 3 || y < -5 || y == "") {
        document.getElementById("error_box").innerHTML = "Y must be from -5 to 3";
        return false;
    } else {
        document.getElementById("error_box").innerHTML = "";
        return true;
    }
}

function blurYHandler() {
    var y = document.forms["input_form"]["yVal"].value;
    if(checkY())
    {
        globalPoint.y = parseFloat(y);
        showGlobalPoint();
    }
}

function checkR() {
    var r = getCheckboxValue(document.getElementsByClassName("rCheckbox"));
    if (r == "") {
        document.getElementById("error_box").innerHTML = "Select the R value";
        return false;
    }
    return true;
}

function imageClickHandler(e) {
    var evt = window.event || e;
    if(checkR()) {
        var r = getCheckboxValue(document.getElementsByClassName("rCheckbox"));
        var posX = evt.offsetX?(evt.offsetX):evt.pageX-document.getElementById("graph_img").offsetLeft;
        var posY = evt.offsetY?(evt.offsetY):evt.pageY-document.getElementById("graph_img").offsetTop;
        posX = posX - 102;
        posY = -(posY - 102);

        var normR = 79/r;
        globalPoint.r = r;
        globalPoint.x = (posX/normR).toFixed(2);
        globalPoint.y = (posY/normR).toFixed(2);
        console.log("x = " + globalPoint.x);
        console.log("y = " + globalPoint.y);
        showGlobalPoint();
    }
}

function checkedHandler(e) {
    if(checkR()) {
        var evt = window.event || e;
        var group = document.getElementsByClassName("rCheckbox");
        globalPoint.r = getCheckboxValue(group);
        for (var i = 0, iLen = group.length; i < iLen; i++) {
            if (group[i] !== evt.target) {
                group[i].checked = false;
            }
        }
    }
}

function showGlobalPoint() {
    if( globalPoint.x != null && globalPoint.y != null)
        document.getElementById("pointToCheck").innerHTML = "("+globalPoint.x+"; "+globalPoint.y+")";
}

