var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({port: 8081});
var Obj = [
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "swipe_up",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "swipe_right",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "swipe_down",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "swipe_left",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "click",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "back",
	  "points" : ""
	},
		{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "map",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "email",
	  "points" : ""
	},
	{
	  "demo" : "youtube",
	  "action" : "test2",
	  "result" : "music",
	  "points" : ""
	}
];


wss.on('connection', function(ws) {
    ws.on('message', function(message) {
        console.log('received: %s', message);
        var tmp = Math.floor((Math.random() * 9) + 0);
        console.log(JSON.stringify(Obj[tmp]));
        ws.send(JSON.stringify(Obj[tmp]));
    });
    ws.send("connection");
});