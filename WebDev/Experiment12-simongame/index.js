var buttonColors = ["green", "red", "yellow", "blue"];
var gamePattern = [];
var userPattern = [];
var level = 0;
var started = false;

$(".btn").click(function() {
  var buttonId = $(this).attr("id");
  userPattern.push(buttonId);
  playAnimation(buttonId);
  playSound(buttonId);
  checkAnswer(userPattern.length - 1)
});

$(document).on("keydown", function() {
  if (!started) {
    nextSequence();
    started = true;
  }
});

function nextSequence() {
  userPattern = [];
  var randomNumber = Math.floor(Math.random() * 4);
  var nextColor = buttonColors[randomNumber];
  gamePattern.push(nextColor);
  playSound(nextColor);
  playAnimation(nextColor);
  $("h1").text("Level " + level);
  level++;
}

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

function checkAnswer(currentLevel) {
  if (userPattern[currentLevel] === gamePattern[currentLevel]) {
    if (currentLevel + 1 === level) {
      setTimeout(function() {
        nextSequence();
      }, 1000);
    }
  } else {
    var audio = new Audio("sounds/wrong.mp3");
    audio.play();
    $("h1").text("Game Over, Press Any Key To Restart");
    $("body").toggleClass("game-over");
    setTimeout(function() {
      $("body").toggleClass("game-over");
    }, 200);
    startOver();
  }
}

function startOver() {
  level = 0;
  gamePattern = [];
  started = false;
}
