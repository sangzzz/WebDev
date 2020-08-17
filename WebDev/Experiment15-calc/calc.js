const express = require("express");
const bodyParser = require("body-parser")
const app = express();

app.get('/', function(req, res) {
  res.sendFile(__dirname + "/index.html");
});

app.use(bodyParser.urlencoded({
  extended: true
}));

app.post('/', function(req, res) {
  var num1 = req.body.Num1;
  var num2 = req.body.Num2;

  var result = Number(num1) + Number(num2);
  // console.log(req.body);
  res.send('The result of the calculation is ' + result);
});

app.get('/bmicalculator', function(req, res) {
  res.sendFile(__dirname + "/bmicalc.html");
});

app.post('/bmicalculator', function(req, res) {
  var weight = parseFloat(req.body.weight);
  var height = parseFloat(req.body.height);
  
  // console.log(req.body);
  // console.log(result2);
  // console.log("hjaska");
  res.send('The result of the calculation is ' + (weight/(height * height)));
});

app.listen(3000, function() {
  console.log("server set up");
});
