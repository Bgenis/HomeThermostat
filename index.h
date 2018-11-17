const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div id="demo">
<h1>Termostat</h1>
    <button type="button" onclick="sendData(1)">Read Temperature</button>
    <button type="button" onclick="sendData(0)">Read Humidity</button><BR>
</div>

<div>
    Temperature is : <span id="TempValue">0</span><br>
    Humidity  is : <span id="HumValue">0</span>
</div>
<script>
function sendData(temperature) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("TempValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setTemp?TempValue="+temperature, true);
  xhttp.send();
}


getData("readTemp", getTemp);
getData("readHum", getHum);

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData("readTemp", getTemp);
  getData("readHum", getHum);
}, 200); //2000mSeconds update rate

function getData(url, cFunction) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) 
    {
        cFunction(this);
    }
  };
  xhttp.open("GET", url, true);
  xhttp.send();
}
function getTemp(xhttp) {
      document.getElementById("TempValue").innerHTML =
      xhttp.responseText;
}
function getHum(xhttp) {
      document.getElementById("HumValue").innerHTML =
      xhttp.responseText;
}
</script>
</body>
</html>
)=====";