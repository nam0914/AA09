// tcp server (network server)
var net = require('net');
var port = 3000;

// Network connection using socket
var server = net.createServer(function( socket ) {
	console.log("Connection from " + socket.remoteAddress);
	socket.end("Hello AA00! from localhost:3000");
});

server.listen(port, "127.0.0.1");
console.log("Network server started at port : " + port);
