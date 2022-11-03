// cds_dht22_node.js

var serialport = require("serialport");
var portName = "COM3"; // check your COM port!
var port = process.env.PORT || 3000;

var io = require("socket.io").listen(port);

const Readline = require("@serialport/parser-readline");
// serial port object
var sp = new serialport(portName, {
  baudRate: 9600, // 9600  38400
  dataBits: 8,
  parity: "none",
  stopBits: 1,
  flowControl: false,
  parser: new Readline("\r\n"),
});

const parser = sp.pipe(new Readline({ delimiter: "\r\n" }));

// Read the port data
sp.on("open", () => {
  console.log("serial port open");
});

var dStr = "";
var readData = ""; // this stores the buffer
var temp = "";
var humi = "";
var lux = "";
var mdata = []; // this array stores date and data from multiple sensors
var firstcommaidx = 0;

parser.on("data", (data) => {
  // call back when data is received
  readData = data.toString(); // append data to buffer
  firstcommaidx = readData.indexOf(",");
  // parsing data into signals
  if (readData.lastIndexOf(",") > firstcommaidx && firstcommaidx > 0) {
    temp = readData.substring(0, firstcommaidx);
    humi = readData.substring(
      firstcommaidx + 1,
      readData.indexOf(",", firstcommaidx + 1)
    );
    lux = readData.substring(readData.lastIndexOf(",") + 1);
    readData = "";
    dStr = getDateString();
    mdata[0] = dStr; // Date
    mdata[1] = temp; // temperature data
    mdata[2] = humi; // humidity data
    mdata[3] = lux; // luminosity data
    console.log("AAnn," + mdata);
    io.sockets.emit("message", mdata); // send data to all clients
  } else {
    // error
    console.log(readData);
  }
});

io.sockets.on("connection", function (socket) {
  // If socket.io receives message from the client browser then
  // this call back will be executed.
  socket.on("message", function (msg) {
    console.log(msg);
  });
  // If a web browser disconnects from Socket.IO then this callback is called.
  socket.on("disconnect", function () {
    console.log("disconnected");
  });
});

// helper function to get a nicely formatted date string
function getDateString() {
  var time = new Date().getTime();
  // 32400000 is (GMT+9 Korea, GimHae)
  // for your timezone just multiply +/-GMT by 3600000
  var datestr = new Date(time + 32400000)
    .toISOString()
    .replace(/T/, " ")
    .replace(/Z/, "");
  return datestr;
}
