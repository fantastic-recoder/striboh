import { Injectable } from '@angular/core';

import { encode, decode } from 'msgpack-lite';

import { HttpClient } from '@angular/common/http';
import { ClientRequest } from 'http';

interface EchoUuidResponse {
    svc: {
        path: string;
        result: boolean;
        uuid_arr: Uint8Array;
        uuid: string;
    };
}

interface EchoResponse {
    siid: string;
    mthd: string;
    prms: { p0: string };
    type: 1;
}

@Injectable({
    providedIn: 'root'
})
export class HelloService {

    private mUuid: Uint8Array | undefined;
    private mWebSocket: WebSocket | undefined;
    private mEchoPar: string | undefined;
    private mEchoReturn: Function | undefined;


    private onWsMessage(pEvent: MessageEvent) {
        const myBlob: Blob = pEvent.data;
        myBlob.arrayBuffer().then((pBuffer: ArrayBuffer) => {this.onBuffer(pBuffer); });
    }

    onBuffer(pBuffer: ArrayBuffer) {
        console.log('Received:' + pBuffer);
        const myReplyObj = decode(new Uint8Array(pBuffer));
        console.log(myReplyObj);
        if (this.mEchoReturn != undefined) {
            this.mEchoReturn(myReplyObj.rtrn);
        }
        else {
            console.error('this.m_EchoReturn==undefined');
        }
    }

    private onWsOpen(): void {
        console.log('Connected to Server via WS.');
        if (this.mEchoPar !== undefined) {
            this.doSendEcho(this.mEchoPar);
        } else {
            console.error('Echo par is undefined!');
        }
    }

    private doSendEcho(pP0: string) {
        if(this.mWebSocket !== undefined) {
            const data = {siid: this.mUuid, mthd: 'echo', prms: {p0: pP0}, type: 1};
            const encoded = encode(data);
            this.mWebSocket.send(encoded);
            console.log('Sending:' + JSON.stringify(data) + '.');
        }
    }

    private onReceiveUiid(pEchoUuidResponse: EchoUuidResponse) {
        this.mUuid = pEchoUuidResponse.svc.uuid_arr;
        console.log('UUID Response:' + this.mUuid);
        this.mWebSocket = new WebSocket('ws://localhost:63898/m0/m1/Hello?upgrade');
        this.mWebSocket.onopen = () => { this.onWsOpen(); };
        this.mWebSocket.onerror = (pError: any) => {
            console.log(`WebSocket error: ${pError}`);
        };
        this.mWebSocket.onclose = () => {
            console.log('Websocked closed');
            this.mUuid = new Uint8Array();
        };
        this.mWebSocket.onmessage = (pEvent: MessageEvent) => {this.onWsMessage(pEvent); };
    }

    onUiidReceiveError(e: any) {
        console.log('problem with request: ' + e.message);
    }

    retrieveUuid() {
        this.mHttp.get<EchoUuidResponse>('http://localhost:63898/m0/m1/Hello?svc')
            .subscribe((pEchoUuidResponse: EchoUuidResponse) => {this.onReceiveUiid(pEchoUuidResponse); }, this.onUiidReceiveError);
    }

    constructor(private mHttp: HttpClient) { }

    public echo(p0: string, pReturn: Function): void {
        this.mEchoReturn = pReturn;
        this.mEchoPar = p0;
        console.log('p0:' + this.mEchoPar);
        if(this.mUuid !== undefined && this.mUuid.length === 16) {
            this.doSendEcho(this.mEchoPar);
        } else {
            this.retrieveUuid();
        }
    }

}
