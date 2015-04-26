function validateForm() {
    var y = document.forms["input_form"]["yVal"].value;
    var x = getRadioValue(document.forms["input_form"]["xVal"]);
    var r = getRadioValue(document.forms["input_form"]["rVal"]);
    console.log(x);
    if (x == "") {
        document.getElementById("error_box").innerHTML = "Please, select the X value";
        return false;
    }
    if (y > 3 || y < -3 || y == "") {
        document.getElementById("error_box").innerHTML = "Y must be from -3 to 3";
        return false;
    }
    if (r == "") {
        document.getElementById("error_box").innerHTML = "Please, select the R value";
        return false;
    }
}

function getRadioValue(group) {
    for (var i=0, iLen=group.length; i<iLen; i++) {
        if (group[i].checked) {
            return group[i].value;
        }
    }
    return '';
}

