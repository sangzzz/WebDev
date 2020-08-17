//jshint esversion:6
require("dotenv").config();
const express = require("express");
const ejs = require("ejs");
const mongoose = require("mongoose");
const encrypt = require("mongoose-encryption");
const md5 = require("md5");
const session = require("express-session");
const passport = require("passport");
const passportLocalMongoose = require("passport-local-mongoose");

const app = express();

app.set("view engine", "ejs");
app.use(
  express.urlencoded({
    extended: true,
  })
);

app.use(
  session({
    secret: process.env.SECRET,
    resave: false,
    saveUninitialized: false,
  })
);

app.use(passport.initialize());
app.use(passport.session());

mongoose.connect("mongodb://localhost:27017/UserDB", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

const userSchema = new mongoose.Schema({
  username: String,
  password: String,
  secret: String,
});

// userSchema.plugin(encrypt, {secret: process.env.SECRET, encryptedFields: ["password"]});
userSchema.plugin(passportLocalMongoose);

const userModel = new mongoose.model("user", userSchema);

passport.use(userModel.createStrategy()); //This strategy is then referred as 'local' strategy
passport.serializeUser(userModel.serializeUser());
passport.deserializeUser(userModel.deserializeUser());

app.get("/", function (req, res) {
  res.render("home");
});

app.get("/login", function (req, res) {
  res.render("login");
});

app.get("/register", function (req, res) {
  res.render("register");
});

app.get("/submit", function (req, res) {
  if (req.isAuthenticated()) {
    res.render("submit");
  } else {
    res.redirect("/login");
  }
});

app.get("/secrets", function (req, res) {
  if (req.isAuthenticated()) {
    userModel.find({ secret: { $exists: true } }, function (err, users) {
      if (err) {
        console.log(err);
      } else {
        if (users) {
          res.render("secrets", { usersWithSecrets: users });
        }
      }
    });
  } else {
    res.redirect("/login");
  }
});

app.get("/logout", function (req, res) {
  req.logout();
  res.redirect("/");
});

app.post("/submit", function (req, res) {
  const submittedSecret = req.body.secret;
  userModel.findById(req.user.id, function (err, user) {
    if (err) {
      console.log(err);
    } else {
      if (user) {
        user.secret = submittedSecret;
        user.save(function (err) {
          if (!err) {
            res.redirect("/secrets");
          }
        });
      }
    }
  });
});

app.post("/login", function (req, res) {
  // userModel.findOne({
  //   username: req.body.username,
  //   password: req.body.password
  // }, function(err, foundUser) {
  //   if(!err){
  //     if(!foundUser){
  //       res.send("Invalid User Details");
  //     }
  //     else{
  //       res.render("secrets");
  //     }
  //   }
  // });

  // userModel.findOne({
  //   username: req.body.username
  // }, function(err, foundUser) {
  //   if (err) {
  //     console.log(err);
  //   } else {
  //     if (foundItem) {
  //       if (foundUser.password === md5(req.body.password)) {
  //         res.render("secrets");
  //       } else {
  //         res.send("Check Your Username Once!");
  //       }
  //     } else {
  //       res.send("Please Register First")
  //     }
  //   }
  // });

  const user = new userModel({
    username: req.body.username,
    password: req.body.password,
  });

  req.login(user, function (err) {
    if (err) {
      console.log(err);
      res.redirect("/login");
    } else {
      passport.authenticate("local")(req, res, function () {
        res.redirect("/secrets");
      });
    }
  });
});

app.post("/register", function (req, res) {
  // const newUser = new userModel({
  //   username: req.body.username,
  //   password: md5(req.body.password)
  // });
  // newUser.save(function(err) {
  //   if (!err) {
  //     res.render("secrets");
  //   } else {
  //     res.send(err);
  //   }
  // });

  userModel.register(
    { username: req.body.username },
    req.body.password,
    function (err, user) {
      if (err) {
        console.log(err);
        res.redirect("/register");
      } else {
        passport.authenticate("local")(req, res, function () {
          res.redirect("/secrets");
        });
      }
    }
  );
});

app.listen(3000, function (err) {
  console.log("Server running on port 3000");
});
