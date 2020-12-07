"use strict";
exports.__esModule = true;
var msgpack_lite_1 = require("msgpack-lite");
var http = require("http");
var WebSocket = require("ws");
var options = {
    hostname: '127.0.0.1',
    port: 63898,
    path: '/m0/m1/Hello?svc',
    method: 'GET'
};
var theUuid;
var req = http.request(options, function (res) {
    console.log('STATUS: ' + res.statusCode);
    console.log('HEADERS: ' + JSON.stringify(res.headers));
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
        console.log('Response: ' + chunk);
        var jsonParsed = JSON.parse(chunk);
        theUuid = jsonParsed.svc.uuid_arr;
        console.log('UUID: ' + jsonParsed.svc.uuid);
    });
    res.on('end', function (chunk) {
        console.log('Response ENDED');
    });
});
req.on('error', function (e) {
    console.log('problem with request: ' + e.message);
});
var aWs = new WebSocket('ws://localhost:63898/m0/m1/Hello?upgrade');
aWs.on('open', function open() {
    console.log('Connected to Server via WS.');
    var data = { "siid": theUuid, "mthd": "echo", "prms": { "p0": "Paul" }, "type": 1 };
    var encoded = msgpack_lite_1.encode(data);
    aWs.send(encoded);
});
aWs.onerror = function (error) {
    console.log("WebSocket error: " + error);
};
aWs.onmessage = function (e) {
    //console.log(e);
    var myReplyObj = msgpack_lite_1.decode(e.data);
    console.log(myReplyObj);
    aWs.close();
};
req.end();
