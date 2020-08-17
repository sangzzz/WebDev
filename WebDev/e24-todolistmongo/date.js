module.exports.getDate = function(){
  let today = new Date();
  let options = {
    weekday: "long",
    year: "numeric",
    month: "long"
  };
  let day = today.toLocaleDateString("en-US", options);
  return day;
};

module.exports.getDay = function(){
  let today = new Date();
  let options = {
    weekday: "long"
  };
  let day = today.toLocaleDateString("en-US", options);
  return day;
}
