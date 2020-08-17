const express = require("express");
const mongoose = require("mongoose");
const _ = require("lodash");
const cors = require("cors");

const app = express();

mongoose
  .connect("mongodb://localhost:27017/BloodBank", {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  })
  .then();

app.set("port", 5000);
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cors());

const userSchema = new mongoose.Schema({
  _SSN: String,
  EMAIL: String,
  PASSWORD: String,
  DNAME: {
    FNAME: String,
    LNAME: String,
  },
  DOB: Date,
  BLOOD_TYPE: String,
  COUNTRY: String,
});

const donorSchema = new mongoose.Schema({
  _DSSN: String,
  EMAIL: String,
  PASSWORD: String,
  DNAME: {
    FNAME: String,
    LNAME: String,
  },
  DOB: Date,
  BLOOD_TYPE: String,
  COUNTRY: String,
  CAMP: {
    CAMP_ID: String,
    CAMP_LOCATION: String,
  },
});

const patientSchema = new mongoose.Schema({
  _PSSN: String,
  EMAIL: String,
  PASSWORD: String,
  PNAME: {
    FNAME: String,
    LNAME: String,
  },
  DOB: Date,
  BLOOD_TYPE: String,
  COUNTRY: String,
  URGENCY: String,
  DATE_OF_REQUEST: Date,
  HOSPITAL: {
    HOSPITAL_ID: String,
    HOSPITAL_NAME: String,
  },
});

const campSchema = new mongoose.Schema({
  _CAMP_ID: String,
  LOCATION: String,
  HOSPITAL: {
    HOSPITAL_ID: String,
    HOSPITAL_NAME: String,
  },
});

const sponsorSchema = new mongoose.Schema({
  _SPONSOR_ID: String,
  SPONSOR_NAME: String,
  EMAIL: String,
  AMOUNT: Number,
  HOSPITAL: {
    HOSPITAL_ID: String,
    HOSPITAL_NAME: String,
  },
});

const hospitalSchema = new mongoose.Schema({
  _HOSPITAL_ID: String,
  HOSPITAL_NAME: String,
  NUM_OF_PATIENTS: Number,
});

const User = mongoose.model("User", userSchema);
const Donor = mongoose.model("Donor", donorSchema);
const Patient = mongoose.model("Patient", patientSchema);
const Camp = mongoose.model("Camp", campSchema);
const Hospital = mongoose.model("Hospital", hospitalSchema);
const Sponsor = mongoose.model("Sponsor", sponsorSchema);

app.post("/login", (req, res) => {
  console.log(req.body);

  const newUser = new User({
    EMAIL: req.body.user.email,
    PASSWORD: req.body.user.password,
  });
  newUser.save((err) => {
    if (err) {
      res.send(err);
    } else {
      res.send("Success!");
    }
  });
});

app.listen(5000, () => console.log("Server is running in port 5000"));
