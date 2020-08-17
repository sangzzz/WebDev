x=document.querySelectorAll(".drum")
y=x.length
while(y>0)
{
  x[y-1].addEventListener("click",function (){
    var buttonClicked=this.innerHTML;
    playSound(buttonClicked);
    playAnimation(event.key);
  });
  y=y-1;
}

document.addEventListener("keydown",function(event){
  playSound(event.key);
  playAnimation(event.key);
});

function playAnimation(keyPressed){
  document.querySelector("."+keyPressed).classList.toggle("pressed");
  // document.addEventListener("keyup",function(event){
  //   document.querySelector("."+event.key).classList.toggle("pressed");
  // })
  setTimeout(function(){document.querySelector("."+keyPressed).classList.toggle("pressed");},100)
}


function playSound(keyPressed){
  switch(keyPressed)
  {
    case "w":
      var tom1=new Audio("sounds/tom-1.mp3");
      tom1.play();
    break;
    case "a":
      var tom2=new Audio("sounds/tom-2.mp3");
      tom2.play();
    break;
    case "s":
      var tom3=new Audio("sounds/tom-3.mp3");
      tom3.play();
    break;
    case "d":
      var tom4=new Audio("sounds/tom-4.mp3");
      tom4.play();
    break;
    case "j":
      var snare=new Audio("sounds/snare.mp3");
      snare.play();
    break;
    case "k":
      var crash=new Audio("sounds/crash.mp3");
      crash.play();
    break;
    case "l":
      var kick=new Audio("sounds/kick-bass.mp3");
      kick.play();
    break;
  }
}
