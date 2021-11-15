import { Injectable } from '@angular/core';

import { encode, decode } from 'msgpack-lite';

import { HttpClient } from "@angular/common/http";
import { ClientRequest, IncomingMessage } from 'http';
import { hasUncaughtExceptionCaptureCallback } from 'process';
//import { HttpClientModule } from '@angular/common/http';

interface EchoUuidResponse {
    svc: {
        path: string,
        result: boolean,
        uuid_arr: Uint8Array,
        uuid: string
    }
}

interface EchoResponse {
    "siid": string,
    "mthd": string,
    "prms": { "p0": string },
    "type": 1
}

@Injectable({
    providedIn: 'root'
})
export class HelloService {

    private m_Uuid: Uint8Array | undefined;

    private m_WebSocket: WebSocket | undefined;

    private m_HttpRequest: ClientRequest | undefined;
    private m_EchoPar: string | undefined;
    private m_EchoReturn: Function | undefined;


    private onWsMessage(p_Event: MessageEvent) {
        const myBlob: Blob = p_Event.data;
        myBlob.arrayBuffer().then((p_Buffer:ArrayBuffer)=>{this.onBuffer(p_Buffer)})
    }

    onBuffer(p_Buffer: ArrayBuffer) {
        console.log("Received:"+p_Buffer);
        let myReplyObj = decode(new Uint8Array(p_Buffer));
        console.log(myReplyObj);
        this.m_WebSocket?.close();
        if(this.m_EchoReturn!=undefined) {
            this.m_EchoReturn(myReplyObj.rtrn);
        }
        else {
            console.error('this.m_EchoReturn==undefined');
        }
    }

    private onWsOpen(): void {
        console.log('Connected to Server via WS.');
        let data = { "siid": this.m_Uuid, "mthd": "echo", "prms": { "p0": this.m_EchoPar }, "type": 1 };
        let encoded = encode(data);
        this.m_WebSocket?.send(encoded);
    }

    private onReceiveUiid(p_EchoUuidResponse: EchoUuidResponse) {
        this.m_Uuid = p_EchoUuidResponse.svc.uuid_arr;
        console.log("UUID Response:" + this.m_Uuid);
        this.m_WebSocket = new WebSocket('ws://localhost:63898/m0/m1/Hello?upgrade');
        this.m_WebSocket.onopen = ()=>{this.onWsOpen();}
        this.m_WebSocket.onerror = (pError: any) => {
            console.log(`WebSocket error: ${pError}`)
        };
        this.m_WebSocket.onmessage = (p_Event: MessageEvent)=>{this.onWsMessage(p_Event);};
    }

    onUiidReceiveError(e: any) {
        console.log('problem with request: ' + e.message)
    }

    retrieveUuid() {
        this.m_Http.get<EchoUuidResponse>("http://localhost:63898/m0/m1/Hello?svc").subscribe((p_EchoUuidResponse: EchoUuidResponse)=>{this.onReceiveUiid(p_EchoUuidResponse);}, this.onUiidReceiveError);
    }

    constructor(private m_Http: HttpClient) { }

    public echo(p0: string, pReturn: Function): void {
        this.m_EchoReturn = pReturn;
        this.m_EchoPar = p0;
        console.log('p0:'+this.m_EchoPar);
        this.retrieveUuid();
    }

}


