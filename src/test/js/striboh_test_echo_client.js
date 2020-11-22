import { encode, decode } from '@msgpack/msgpack';

const msgpack = require("@msgpack/msgpack");

const http = require('http');
const WebSocket = require('ws');


const options = {
    hostname: '127.0.0.1',
    port: 63898,
    path: '/m0/m1/Hello?svc',
    method: 'GET'
};

let theUuid = [];

const req = http.request(options, function (res) {
    console.log('STATUS: ' + res.statusCode);
    console.log('HEADERS: ' + JSON.stringify(res.headers));
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
        console.log('Response: ' + chunk);
        let jsonParsed = JSON.parse(chunk);
        theUuid = jsonParsed.svc.uuid_arr;
        console.log('UUID: ' + jsonParsed.svc.uuid);
    });
    res.on('end', function (chunk) {
        console.log('Response ENDED');
    });
});

req.on('error', function(e) {
    console.log('problem with request: ' + e.message);
});

const ws = new WebSocket('ws://localhost:63898/m0/m1/Hello?upgrade');

ws.on('open', function open() {
    console.log('Connected to Server via WS.');
    const data = {"siid":theUuid,"mthd":"echo","prms":{"p0":"Paul"},"type":1};
    let encoded = msgpack.encode(data);
    ws.send(encoded);
})

ws.onerror = (error) => {
    console.log(`WebSocket error: ${error}`)
}

ws.onmessage = (e) => {
    //console.log(e);
    let myReplyObj = msgpack.decode(e.data);
    console.log(myReplyObj)
    ws.close();
}

req.end();
