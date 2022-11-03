// cds_dht22_express.js  
// Express


var web_port = 3030;  // express port

// MongoDB
var mongoose = require('mongoose');
var Schema = mongoose.Schema;  // Schema object
// MongoDB connection
mongoose.connect('mongodb://localhost:27017/'); // DB name
var db = mongoose.connection;    
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback () {
        console.log("mongo db connection OK.");
});

// Schema
var iotSchema = new Schema({
    




});
var Sensor = mongoose.model("Sensor", iotSchema);  // sensor data model

// Web routing addrebss
app.get('/', function (req, res) {  // localhost:3030/
  res.send('Hello Arduino IOT: express server by AA00!');
});
// find all data & return them
app.get('/', function (req, res) {
    Sensor.find(function(err, data) {
        
    });
});
// find data by id
app.get('/iot/:id', function (req, res) {
    Sensor.findById(req.params.id, function(err, data) {
        res.json(data);
    });
});

// Express WEB
app.use(express.static(__dirname + ));  // WEB root folder -> public
app.listen();  // port 3030
console.log("Express_IOT is running at port:3030");
