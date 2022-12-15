// express33rgb.js  =< nano33imu_ex.js
// Express with CORS
var express = require('express');
var cors = require('cors');  // CORS: Cross Origin Resource Sharing
var app = express();
// CORS 
app.use(cors());

var web_port = 3030;  // express port
// MongoDB
var mongoose = require('mongoose');
var Schema = mongoose.Schema;  // Schema object
// MongoDB connection
mongoose.connect('mongodb://localhost:27017/iot33imu', {  // DB name  
    useNewUrlParser: true,
    useUnifiedTopology: true,
  }); 
var db = mongoose.connection;    
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback () {
        console.log("mongo db connection OK.");
});
// Schema
var iotSchema = new Schema({
    date : String,
    accel_x : String,
    accel_y : String,
    accel_z : String,
    gyro_x : String,
    gyro_y : String,
    gyro_z : String,
    mag_x : String,
    mag_y : String,
    mag_z : String    
});
var Sensor = mongoose.model("Sensor", iotSchema);  // sensor data model

// Web routing address
app.get('/', function (req, res) {  // localhost:3030/
  res.send('Hello Arduino nano 33 BLE IMU!');
});
// find all data & return them
app.get('/iot', function (req, res) {
    Sensor.find(function(err, data) {
        res.json(data);
    });
});
// find data by id
app.get('/iot/:id', function (req, res) {
    Sensor.findById(req.params.id, function(err, data) {
        res.json(data);
    });
});

// Express WEB
app.use(express.static(__dirname + '/public'));  // WEB root folder
app.listen(web_port);  // port 3030
console.log("Express_nano33_IoT is running at port:3030, CORS powered!");
