const express = require("express");
const app = express();

app.get("/",function(req,res){
    // console.log(req);
    // res.send("homepage/tindog.html");
    res.send("<h1>I'm in 3000, YO!!!</h1>")
});

app.get("/about",function(req,res){
  res.send("<p> I am a student at Nitk. yeahhh!</p>");
});

app.listen(3000,function(){
  // console.log("i'm in 3000,yo");
});
