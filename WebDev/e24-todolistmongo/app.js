const express = require("express");
const ejs = require("ejs");
const date = require(__dirname + "/date.js");
const mongoose = require("mongoose");
const lodash = require("lodash");

const app = express();

mongoose.connect("mongodb://localhost:27017/TasksDB", {
  useNewUrlParser: true,
  useUnifiedTopology: true
});

taskSchema = new mongoose.Schema({
  task: {
    type: String,
    required: [true, "Enter a fucking task, you dipshit"]
  }
});

const taskModel = mongoose.model("Task", taskSchema);

const task1 = new taskModel({
  task: "Welcome to your To Do List!"
});

const task2 = new taskModel({
  task: "Hit the + button to add a new item."
});

const task3 = new taskModel({
  task: "<-- Hit this to delete an item."
});

const defaultItems = [task1, task2, task3];

const newListSchema = new mongoose.Schema({
  name: String,
  list: [taskSchema]
});

const newListModel = mongoose.model("list", newListSchema);

// taskModel.deleteMany({_id: {$in: ["5eb3e30d2e43724664f10357","5eb3e30d2e43724664f10358","5eb3e30d2e43724664f10359"]}},function(err){
//   if(err){
//     console.log(err);
//   }
//   else{
//     console.log("Delete Successful!");
//   }
// });
//
// let tasks = [];
// let workTasks = [];

let page = "";

app.use(express.urlencoded({
  extended: true
}));

app.set("view engine", "ejs");

app.use(express.static("public"));

app.get("/", function(req, res) {


  taskModel.find({}, function(err, listItems) {
    if (err) {
      console.log(err);
    } else {
      if (listItems.length === 0) {

        taskModel.insertMany(defaultItems, function(err) {
          if (err) {
            console.log(err);
          } else {
            console.log("Success!");
          }
        });
        res.redirect("/");
      } else {

        let day = date.getDate();
        page = "Today"
        res.render("list", {
          today: "Today",
          addTask: listItems
        });
      }
    }

  });


});


app.get("/:listName", function(req, res) {
  const newListName = lodash.capitalize(req.params.listName);

  newListModel.findOne({
    name: newListName
  }, function(err, foundList) {
    if (!foundList) {
      const addlist = new newListModel({
        name: newListName,
        list: defaultItems
      });
      addlist.save();
      res.redirect("/" + newListName);
    } else {
      page = newListName;
      res.render("list", {
        today: lodash.capitalize(foundList.name),
        addTask: foundList.list
      });
    }
  });

});

app.get("/about", function(req, res) {
  res.render("about");
});

app.post("/", function(req, res) {
  const urlEnd = req.body.list;

  const itemName = req.body.task;
  const newTask = new taskModel({
    task: itemName
  });

  if (urlEnd === "Today") {
    newTask.save();
    res.redirect("/");
  } else {
    newListModel.findOne({
      name: urlEnd
    }, function(err, foundList) {
      if (!err) {
        foundList.list.push(newTask);
        foundList.save();
        res.redirect("/" + urlEnd);
      }
    })
  }
});

app.post("/delete", function(req, res) {
  const id = req.body.del;
  console.log(id);
  if (page === "Today") {
    taskModel.deleteOne({
      _id: id
    });
    res.redirect("/");
  }
  else{

    newListModel.findOneAndUpdate({name:page},{$pull: {list: {_id:id}}},function(err,result){
      if(err){
        console.log(err);
      }
      else{
        console.log("Success");
      }
    });
    res.redirect("/"+page);
    // newListModel.findOne({name:page},function(err,foundList){
    //   if(!err){
    //     foundList.list.forEach(function(task){
    //       console.log(task);
    //       if (task._id==id){
    //         foundList.list.pop(task);
    //         foundList.save();
    //         res.redirect("/"+page);
    //       }
    //     });
    //   }
    // });

  }
});



app.listen(3000, function() {
  console.log("Server up on port 3000");
});
