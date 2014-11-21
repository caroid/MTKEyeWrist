//websocket Linkit Clientside
var WebSocket = require('ws');
var ws = new WebSocket('ws://127.0.0.1:8081');
var Client_socket;
ws.on('open', function() {
    ws.send('LinkitServerConnect');
});
ws.on('message', function(data, flags) {
    if (data!="connection")
    {
        //console.log(data);
        var jsonData = JSON.parse(data);
        console.log(jsonData.demo+","+jsonData.result);
        if (Client_socket)
        {
            Client_socket.write(jsonData.demo+","+jsonData.result);
        };
    }
});



//TCP Socket with Linkit
var net = require('net');
var server = net.createServer();


server.on('listening', function () {

});

server.on('connection', function (socket) {
    //socket.pipe(socket);
    Client_socket = socket;
    socket.on('data', function (data) {
        if(data == "connection")
        {
            console.log("connect");
            ws.send('Linkit:connect');
        }
        if(data == "test")
        {
            //console.log("dosomething");
            console.log("Send:done");
            ws.send('send');
            //socket.write("done");
        }
    });
});


server.listen(8080);
// require('net').createServer(function (socket) {
//     console.log("connected");
//     socket.on('data', function (data) {
//     	if(data == "connection")
//     	{
//     		console.log("connect");
//             ws.send('Linkit:connect');
//     	}
//     	if(data == "test")
//     	{
//     		console.log("dosomething");
//     		console.log("Send:done");
//             ws.send('Linkit:test')
//     		socket.write("done");
//     	}
//     });
// }).listen(8080);