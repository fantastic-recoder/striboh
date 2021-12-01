import re

import sys
import logging
import pystache

sys.path.append(['../lib', '../../../cmake-build-debug/lib'])

import stribohIdl


class NgVisitorBase:
    def __init__(self):
        logging.debug('NgVisitorBase::__init__')

class NgServantVisitor(NgVisitorBase, stribohIdl.AstVisitor):
    m_module_names: [str]

    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(2)
        logging.debug('NgServantVisitor::__init__')

    def beginRun(self, p_run_num):
        logging.debug('NgServantVisitor::beginRun')

    def beginModule(self, p_module_name):
        logging.debug('NgServantVisitor::beginModule')
        self.m_module_names.append(p_module_name)

    def endModule(self, p_module_name):
        logging.debug('NgServantVisitor::endModule')

    def beginInterface(self, p_interface_name):
        logging.debug('NgServantVisitor::beginInterface')

    def endInterface(self, p_interface_name: str):
        logging.debug('NgServantVisitor::endInterface')

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgServantVisitor::beginMethod')

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgServantVisitor::endMethod')

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgServantVisitor::beginParameter')

########################################################################################################################
# client visitor
########################################################################################################################

module_template="""
import { Injectable } from '@angular/core';

import { encode, decode } from 'msgpack-lite';

import { HttpClient } from '@angular/common/http';

interface {{interface_name}}UuidResponse {
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
export class {{interface_name}}Service {

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

    private onReceiveEchoUiid(p{{interface_name}}UuidResponse: {{interface_name}}UuidResponse): void {
        this.mUuid = p{{interface_name}}UuidResponse.svc.uuid_arr;
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
        this.mHttp.get<{{interface_name}}UuidResponse>('http://localhost:63898/m0/m1/Hello?svc')
            .subscribe((p{{interface_name}}UuidResponse: {{interface_name}}UuidResponse) => {this.onReceiveEchoUiid(p{{interface_name}}UuidResponse); },
                {{interface_name}}Service.onUiidReceiveError);
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
"""

class NgClientVisitor(NgVisitorBase, stribohIdl.AstVisitor):

    m_filename: str
    m_ast = {}

    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(1)
        self.m_run_no = 0
        logging.debug('NgClientVisitor::__init__')

    def getRuns(self) -> int:
        return 2

    def beginRun(self, p_run_no: int):
        logging.debug('NgClientVisitor::beginRun')

    def beginModule(self, p_module_name: str):
        logging.debug(f'NgClientVisitor::beginModule {p_module_name}')

    def endModule(self, p_module_name):
        logging.debug('NgClientVisitor::endModule')

    @staticmethod
    def camel_to_snake(name):
        name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()

    def beginInterface(self, p_interface_name: str):
        logging.debug(f'NgClientVisitor::beginInterface {p_interface_name}')
        self.m_ast = {'interface_name': p_interface_name}
        a_name = '{}.service.ts'.format(p_interface_name)
        self.m_filename = self.camel_to_snake(a_name)

    def endInterface(self, p_interface_name: str):
        logging.debug('NgClientVisitor::endInterface')
        self.addCode(self.m_filename,pystache.render(module_template, self.m_ast))

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgClientVisitor::beginMethod')

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgClientVisitor::endMethod')

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('NgClientVisitor::beginParameter')


my_client_visitor = NgClientVisitor()
my_servant_visitor = NgServantVisitor()


def register():
    logging.info('Registering Angular backend.')
    stribohIdl.setBackendVisitors(my_client_visitor, my_servant_visitor)
