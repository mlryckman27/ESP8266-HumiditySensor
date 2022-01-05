const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <title>DHT22 Test</title>
</head>

<body>

<div>
  <h1> ESP8266 Humidity Sensor </h1>
</div>

<div>
	Humidity Level is: <span id="humidity">NA</span>
</div>

<script>

setInterval(function() {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById("humidity").innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", "/humidity", true)
	xhttp.send();
}, 2000);

</script>

</body>
</html>
)=====";
