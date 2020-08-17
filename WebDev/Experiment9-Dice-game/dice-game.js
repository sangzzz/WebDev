var dice1 = Math.floor(Math.random() * 6);
var dice2 = Math.floor(Math.random() * 6);
document.querySelectorAll(".player1 img")[dice1].style.display = "block";
document.querySelectorAll(".player2 img")[dice2].style.display = "block";

var verdict = "";
if (dice1 > dice2)
  verdict = "Player1 WINS!!!";
else if (dice1 === dice2)
  verdict = "It's a draw, folks. Refresh Again!!!";
else
  verdict = "Player2 WINS!!!";

document.querySelector("h2").innerHTML = verdict;
