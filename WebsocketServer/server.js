var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({port: 8081});
var Obj = [
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "swipe_up",
	  "points" : ""
	},
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "swipe_right",
	  "points" : ""
	},
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "swipe_down",
	  "points" : ""
	},
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "swipe_left",
	  "points" : ""
	},
		{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "map",
	  "points" : ""
	},
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "email",
	  "points" : ""
	},
	{
	  "demo" : "glass",
	  "action" : "test2",
	  "result" : "music",
	  "points" : ""
	}
];


wss.on('connection', function(ws) {
    ws.on('message', function(message) {
        console.log('received: %s', message);
        var tmp = Math.floor((Math.random() * 7) + 0);
        console.log(JSON.stringify(Obj[tmp]));
        ws.send(JSON.stringify(Obj[tmp]));
    });
    ws.send("connection");
});