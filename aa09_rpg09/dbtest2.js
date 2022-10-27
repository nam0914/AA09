// dbtest2.js
var mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/test2", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

var SensorSchema = new mongoose.Schema({
  data: String,
  created: String,
});

// data model
var Sensor = mongoose.model("Sensor", SensorSchema);

var sensor1 = new Sensor({ data: "124", created: getDateString() });
sensor1.save();

var sensor2 = new Sensor({ data: "573", created: getDateString() });
sensor2.save();

console.log("Sensor data were saved in MongoDB");

function getDateString() {
    var time = new Date().getTime();
    // 32400000 is (GMT+9 Korea, GimHae)
    // for your timezone just multiply +/-GMT by 3600000
    var datestr = new Date(time +32400000).
    toISOString().replace(/T/, ' ').replace(/Z/, '');
    return datestr;
}