const http = require('http');
const WebSocket = require('ws');
const MessagePack = require('what-the-pack');

const { encode, decode } = MessagePack.initialize(2**22); // 4MB

const options = {
    hostname: '127.0.0.1',
    port: 63898,
    path: '/m0/m1/Hello?svc',
    method: 'GET'
};

const req = http.request(options, function (res) {
    console.log('STATUS: ' + res.statusCode);
    console.log('HEADERS: ' + JSON.stringify(res.headers));
    res.setEncoding('utf8');
    res.on('data', function (chunk) {
        console.log('Response: ' + chunk);
        let jsonParsed = JSON.parse(chunk);
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
    const data = {"method":"echo","parameters":{"p0":"Paul"},"type":1};
    encoded = encode(data);
    ws.send(encoded);
})

ws.onerror = (error) => {
    console.log(`WebSocket error: ${error}`)
}

ws.onmessage = (e) => {
    console.log(e.data)
}

req.end();
