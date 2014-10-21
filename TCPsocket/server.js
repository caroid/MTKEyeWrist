//websocket Linkit Clientside
var WebSocket = require('ws');
var ws = new WebSocket('ws://127.0.0.1:8081');

ws.on('open', function() {
    ws.send('LinkitServerConnect');
});

//TCP Socket with Linkit
require('net').createServer(function (socket) {
    console.log("connected");

    socket.on('data', function (data) {
    	if(data == "connection")
    	{
    		console.log("connect");
            ws.send('Linkit:connect');
    	}
    	if(data == "test")
    	{
    		console.log("dosomething");
    		console.log("Send:done");
            ws.send('Linkit:test')
    		socket.write("done");
    	}
    });
})

.listen(8080);