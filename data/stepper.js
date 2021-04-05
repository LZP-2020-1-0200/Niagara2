function LoadReading() {
    var xhr_once = new XMLHttpRequest();
    xhr_once.open("GET", "stepper.json", true)
    xhr_once.onload = function () {
        var reading = JSON.parse(xhr_once.responseText);
        console.log(reading);
        document.getElementById("step_delay_usec").value = reading.step_delay_usec;
    }
    xhr_once.send();
}


document.addEventListener('DOMContentLoaded', function () {
    LoadReading();
}, false);