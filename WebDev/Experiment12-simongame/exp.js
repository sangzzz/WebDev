buttonColors = ["green", "red", "yellow", "blue"];
gamePattern = [];
userPattern = [];
// flag = 0;
// $(document).keydown(function(event) {
//
//     $("h1").text("Level "+1)
// });
//

//
//
//    var randomNumberGenerated = nextSequence();
//    var nextColor = buttonColors[randomNumberGenerated];
  // playSound(nextColor);
  // playAnimation(nextColor);
//   gamePattern.push(nextColor);
//   var level = gamePattern.length;
//   $("h1").text("Level " + ())
//   $("button").click(function() {
//     var buttonId = this.attr("id");
//     userPattern.push(buttonId);
//     playAnimation(buttonId);
//     if (gamePattern[i] !== buttonId) {
//       var audio = new Audio("sounds/wrong.mp3")
//       $("h1").text("Game Over, Press Any Key To Restart");
//       gamePattern = [];
//     }
//   });

var randomNumberGenerated = nextSequence();
var nextColor = buttonColors[randomNumberGenerated];
gamePattern.push(nextColor);
playSound(nextColor);
playAnimation(nextColor);
$("button").on("click",function(){
  var userColor = this.attr("id");
  userPattern.push(userColor);
});


function playSound(nextColor) {
  var audio = new Audio("sounds/" + nextColor + ".mp3");
  audio.play();
}

function playAnimation(nextColor) {
  $("#" + nextColor).toggleClass("pressed");
  setTimeout(function() {
    $("#" + nextColor).toggleClass("pressed");
  }, 100);
}

function nextSequence() {
  var randomNumber = Math.floor(Math.random() * 4);
  return randomNumber;
}
