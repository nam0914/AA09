// 'use strict';
// cds_tmp36_node.js

var serialport = require('serialport');
var portName = 'COM3';  // check your COM port!!
var port    =   process.env.PORT || 3000;

var io = require('socket.io').listen(port);

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


var dStr ='';
var readData='';
var temp='';
var lux='';
var mdata=[];
var firstcommaidx = 0;

parser.on('data', (data) => { // call back when data is received
   readData= data.toString(); //.toString('utf-8');
//    console.log(readData);
   firstcommaidx = readData.indexOf(',');
   if(firstcommaidx>0) {
    temp= readData.substring(0,firstcommaidx);
    lux= readData.substring(firstcommaidx+1);
    readData = '';

     dStr=getDateString();
     mdata[0]=dStr;  //date
     mdata[1]=temp;  //data
     mdata[2]=lux;
     console.log('AA00,' + mdata.toString());
     io.sockets.emit('message', mdata);  // send data to all clients  
   }
   else{
        console.log(readData);        
   }
});

io.sockets.on('connection', function (socket) {
    // If socket.io receives message from the client browser then 
    // this call back will be executed.
    socket.on('message', function (msg) {
        console.log(msg);
    });
    // If a web browser disconnects from Socket.IO then this callback is called.
    socket.on('disconnect', function () {
        console.log('disconnected');
    });
});

// helper function to get a nicely formatted date string for IOT
function getDateString() {
    var time = new Date().getTime();
    // 32400000 is (GMT+9 Korea, GimHae)
    // for your timezone just multiply +/-GMT by 3600000
    var datestr = new Date(time +32400000).
    toISOString().replace(/T/, ' ').replace(/Z/, '');
    return datestr;
}