const mongoose = require("mongoose");

mongoose.connect("mongodb://localhost:27017/fruits", {
  useUnifiedTopology: true,
  useNewUrlParser: true
});
//
// const url = "mongodb://localhost:27017";
//
// const dbname = "e23";
//
// const client = new mongodb(url, {
//   useUnifiedTopology: true
// });
//
// client.connect(function(err) {
//   assert.equal(null, err);
//   console.log("Connected Successfully to Server!");
//   const db = client.db(dbname);
//   insertDocuments(db, function() {
//       findDocuments(db, function() {
//         client.close();
//       });
//     });
// });

const fruitSchema = new mongoose.Schema({
  name: {
    type: String,
    required: [true,'Name the fucking fruit!']
  },
  rating: {
    type: Number,
    min: 1,
    max: 10
  },
  review: String
});

const fruit = mongoose.model("Fruit", fruitSchema);
const f = new fruit({

  rating: 5,
  review: "NICE!"
});
 // f.save();
// --> No need to save this data to db multiple times. jUst the once is enough.

const f1 = new fruit({
  name: "Kiwi",
  rating: 4,
  review: "NCE!"
});
const f2 = new fruit({
  name: "Banana",
  rating: 4,
  review: "NIE!"
});
const f3 = new fruit({
  name: "Grapes",
  rating: 10,
  review: "NICEEE! AWESOME SHITT!!"
});

const peopleSchema = new mongoose.Schema({
  name: String,
  age: Number,
  favouriteFruit : fruitSchema
});

const person = mongoose.model("PEople", peopleSchema);
const p = new person({
  name: "Sangeeth",
  age: 20,
  favouriteFruit : f1
});
p.save();
//
// person.deleteMany({name:"Sangeeth"},function(err){
//   if(err){
//     console.log(err);
//   }
//   else{
//     console.log("Deleted Successfully!");
//   }
// });

fruit.updateOne({name:"Apple"},{name:"Peach"},function(err){
  if(err){
    console.log(err);
  }
  else{
    // console.log("Success!");
  }
});

// fruit.insertMany([f1,f2,f3],function(err){
//   if(err){
//     console.log("Failure!");
//   }
//   else{
//     console.log("Success! Fruits Added!");
//   }
// });

fruit.find(function(err, fruits) {
  if (err) {
    console.log(err);
  } else {
    fruits.forEach(function(fruit) {
      console.log(fruit.name);
    });
    // console.log(fruits);
  }
});
//
// fruit.deleteOne({name:"Apple"},function(err){
//   if(err){
//     console.log(err);
//   }
//   else{
//     console.log("Success");
//   }
// })

//
// const insertDocuments = function(db, callback) {
//   // Get the documents collection
//   const collection = db.collection('fruits');
//   // Insert some documents
//   collection.insertMany([{
//     a: 1
//   }, {
//     a: 2
//   }, {
//     a: 3
//   }], function(err, result) {
//     assert.equal(err, null);
//     assert.equal(3, result.result.n);
//     assert.equal(3, result.ops.length);
//     console.log("Inserted 3 documents into the collection");
//     callback(result);
//   });
// }



// const findDocuments = function(db, callback) {
//   // Get the documents collection
//   const collection = db.collection('fruits');
//   // Find some documents
//   collection.find({}).toArray(function(err, docs) {
//     assert.equal(err, null);
//     console.log("Found the following records");
//     console.log(docs)
//     callback(docs);
//   });
// }
