// dbtest.js
var mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

var SensorSchema = new mongoose.Schema({
  data: ,
  created: ,
});

// data model
var Sensor = mongoose.model("Sensor", SensorSchema);

var sensor1 = new Sensor({ data: "124", created: new Date() });
sensor1.save();

var sensor2 = new Sensor({ data: "573", created: new Date() });
sensor2.save();

console.log("Sensor data were saved in MongoDB");
