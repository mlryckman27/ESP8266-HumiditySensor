const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div>
<h1> ESP8266 Humidity Sensor </h1>
	<button type="button" onlcick="updateData()">Update Data</button>
</div>

<div>
	Humidity Level is: <span id="humidityValue">0</span>
</div>

<script>
function updateData() {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			document.getElementById("humidityValue").innerHTML = this.responseText;
		}
	};
	xhttp.open("GET", "readHumidity", true)
	xhttp.send();
}
</script>

</body>
</html>
)=====";

