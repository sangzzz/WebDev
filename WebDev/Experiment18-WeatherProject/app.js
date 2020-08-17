const express = require("express");
const https = require("https");
// const bodyParser = require("body-parser");

const app = express();


app.get("/", function(req, res) {
  res.sendFile(__dirname + "/index.html");
});
//
// app.use(bodyParser.urlencoded({
//   extended: true
// }));

app.use(express.urlencoded({
  extended: true
}));
app.post("/", function(req, res) {

  const query = req.body.cityName;
  const appid = "07ca362beacdaf884f0d65533ce6b157"
  const url = "https://api.openweathermap.org/data/2.5/weather?q=" + query + "&appid=" + appid + "&units=metric";
  https.get(url, function(response) {
    console.log(response.statusCode);

    response.on("data", function(data) {
      const weatherData = JSON.parse(data);
      const temp = weatherData.main.temp;
      const desc = weatherData.weather[0].description;
      const icon = weatherData.weather[0].icon;
      // console.log(desc);
      res.write("<h1>The temperature in " + query + " : " + temp + "C</h1>");
      const iconLink = "http://openweathermap.org/img/wn/" + icon + ".png"
      res.write("<h2>The weather forecast is : " + desc + "<img src = " + iconLink + "></h2>");
      res.send();
    });
  });
});

app.listen(3000, function() {
  console.log("Server running in port 3000");
});
