$("h1").css("color", "red");

$("input").keydown(function(e) {
  $("h1").text(e.key);
});

$("button").click(function(){
  $("h1").animate({opacity : 0.2, size: "120%" });
});
