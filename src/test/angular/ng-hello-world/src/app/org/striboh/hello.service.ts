import { Injectable } from '@angular/core';

import { encode, decode } from 'msgpack-lite';

import { HttpClient } from '@angular/common/http';

interface EchoUuidResponse {
    svc: {
        path: string;
        result: boolean;
        uuid_arr: Uint8Array;
        uuid: string;
    };
}

type EchoReturnFunction = (pReturn: string) => void;

@Injectable({
    providedIn: 'root'
})
export class HelloService {

    private mUuid: Uint8Array | undefined;
    private mWebSocket: WebSocket | undefined;
    private mEchoPar: string | undefined;
    private mEchoReturn: EchoReturnFunction | undefined;

    private static onUiidReceiveError(pError: any): void {
        console.log('problem with request: ' + pError.message);
    }

    private onWsMessage(pEvent: MessageEvent): void {
        const myBlob: Blob = pEvent.data;
        myBlob.arrayBuffer().then((pBuffer: ArrayBuffer) => {this.onBuffer(pBuffer); });
    }

    private onBuffer(pBuffer: ArrayBuffer): void {
        console.log('Received:' + pBuffer);
        const myReplyObj = decode(new Uint8Array(pBuffer));
        console.log(myReplyObj);
        if (this.mEchoReturn !== undefined) {
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

    private doSendEcho(pP0: string): void {
        if (this.mWebSocket !== undefined) {
            const data = {siid: this.mUuid, mthd: 'echo', prms: {p0: pP0}, type: 1};
            this.mWebSocket.send(encode(data));
            console.log('Sending:' + JSON.stringify(data) + '.');
        }
    }

    private onReceiveEchoUiid(pEchoUuidResponse: EchoUuidResponse): void {
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

    private retrieveUuid(): void {
        this.mHttp.get<EchoUuidResponse>('http://localhost:63898/m0/m1/Hello?svc')
            .subscribe((pEchoUuidResponse: EchoUuidResponse) => {this.onReceiveEchoUiid(pEchoUuidResponse); },
                HelloService.onUiidReceiveError);
    }

    constructor(private mHttp: HttpClient) { }

    public echo(p0: string, pReturn: EchoReturnFunction): void {
        this.mEchoReturn = pReturn;
        this.mEchoPar = p0;
        console.log('p0:' + this.mEchoPar);
        if (this.mUuid !== undefined && this.mUuid.length === 16) {
            this.doSendEcho(this.mEchoPar);
        } else {
            this.retrieveUuid();
        }
    }

}
