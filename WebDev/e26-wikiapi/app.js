const mongoose = require("mongoose");
const express = require("express");
const ejs = require("ejs");

const app = express();

app.use(
  express.urlencoded({
    extended: true,
  })
);
app.use(express.static("public"));
app.set("view engine", "ejs");

mongoose.connect("mongodb://localhost:27017/wikiDB", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

const wikiSchema = new mongoose.Schema({
  title: String,
  content: String,
});

const wikiModel = mongoose.model("REST", wikiSchema);

const DOM = new wikiModel({
  title: "DOM",
  content: "It stands for the Document Object Model!",
});

// DOM.save();

// app.get("/articles", function(req, res) {
//   wikiModel.find({}, function(err, articles) {
//     if (!err) {
//       res.send(articles);
//     } else {
//       res.send(err);
//     }
//   });
// });
//
// app.post("/articles", function(req, res) {
//   const article = new wikiModel({
//     title: req.body.title,
//     content: req.body.content
//   });
//   article.save(function(err) {
//     if (err) {
//       res.send(err);
//     } else {
//       res.send("No error! Success.");
//     }
//   });
// });
//
// app.delete("/articles", function(req, res) {
//   wikiModel.deleteMany({}, function(err) {
//     if (err) {
//       res.send(err);
//     } else {
//       res.send("Deleted all documents successfully!");
//     }
//   });
// });

app
  .route("/articles")
  .get(function (req, res) {
    wikiModel.find({}, function (err, articles) {
      if (!err) {
        res.send(articles);
      } else {
        res.send(err);
      }
    });
  })
  .post(function (req, res) {
    const article = new wikiModel({
      title: req.body.title,
      content: req.body.content,
    });
    article.save(function (err) {
      if (err) {
        res.send(err);
      } else {
        res.send("No error! Success.");
      }
    });
  })
  .delete(function (req, res) {
    wikiModel.deleteMany({}, function (err) {
      if (err) {
        res.send(err);
      } else {
        res.send("Deleted all documents successfully!");
      }
    });
  });

app
  .route("/articles/:title")
  .get(function (req, res) {
    const urlEnd = req.params.title;
    wikiModel.findOne(
      {
        title: urlEnd,
      },
      function (err, item) {
        if (!err) {
          res.send(item);
        } else {
          res.send(err);
        }
      }
    );
  })
  .put(function (req, res) {
    wikiModel.updateOne(
      {
        title: req.params.title,
      },
      {
        title: req.body.title,
        content: req.body.content,
      },
      {
        overwrite: true,
      },
      function (err) {
        if (!err) {
          res.send("Successfully Updated the document");
        }
      }
    );
  })
  .patch(function (req, res) {
    wikiModel.updateOne(
      {
        title: req.params.title,
      },
      {
        $set: req.body,
      },
      function (err) {
        if (!err) {
          res.send("No Error!");
        }
      }
    );
  })
  .delete(function (req, res) {
    wikiModel.deleteOne({ title: req.params.title }, function (err) {
      if (!err) {
        res.send("No Error");
      }
    });
  });

app.listen(3000, function (err) {
  if (!err) {
    console.log("Server Running on Port 3000!");
  }
});
