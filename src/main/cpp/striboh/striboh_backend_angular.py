import re
import sys
import logging
import pystache

sys.path.append(['../lib', '../../../cmake-build-debug/lib'])

import stribohIdl as striboh


class NgVisitorBase:

    def __init__(self):
        logging.debug('NgVisitorBase::__init__')


class NgServantVisitor(NgVisitorBase, striboh.AstVisitor):

    def __init__(self):
        striboh.AstVisitor.__init__(self)
        self.setRuns(2)
        logging.debug('NgServantVisitor::__init__')

    def beginRun(self, p_run_num):
        logging.debug('NgServantVisitor::beginRun')

    def beginModule(self, p_module_name):
        logging.debug('NgServantVisitor::beginModule')

    def endModule(self, p_module_name):
        logging.debug('NgServantVisitor::endModule')

    def beginInterface(self, p_interface_name):
        logging.debug('NgServantVisitor::beginInterface')

    def endInterface(self, p_interface_name: str):
        logging.debug('NgServantVisitor::endInterface')

    def beginMethod(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgServantVisitor::beginMethod')

    def endMethod(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgServantVisitor::endMethod')

    def beginParameter(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgServantVisitor::beginParameter')


########################################################################################################################
# client visitor
########################################################################################################################

module_template = """
import {  Inject, Injectable } from '@angular/core';

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

{{#methods}}
type {{method.method_pascal_name}}ReturnFunction = (pReturn: {{method.method_type}}) => void;
{{/methods}}

@Injectable({
    providedIn: 'root'
})
export class {{interface_name}}Service {
    private readonly mHostPortMods;
    private mUuid: Uint8Array | undefined;
    private mWebSocket: WebSocket | undefined;
{{#methods}}
{{#method.parameters}}
    private m{{parameter_name}}Par: {{parameter_type}} | undefined;
{{/method.parameters}}
    private m{{method.method_pascal_name}}Return: {{method.method_pascal_name}}ReturnFunction | undefined;
{{/methods}}

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
        {{#methods}}
        if (myReplyObj.mthd === '{{method.method_name}}') {
          if (this.m{{method.method_pascal_name}}Return !== undefined) {
            this.m{{method.method_pascal_name}}Return(myReplyObj.rtrn);
            return;
          } else {
            console.error('"{{method.method_name}}" return lambda is undefined.');
          }
        }
        {{/methods}}
        console.error('Unknown method "' + myReplyObj.mthd + '".');
    }

{{#methods}}
    private on{{method.method_pascal_name}}WsOpen(): void {
        console.log('Connected to Server via WS.');
        this.doSend{{method.method_pascal_name}}({{#method.parameters}}{{#comma}}, {{/comma}}this.m{{parameter_name}}Par{{/method.parameters}});
    }

{{/methods}}

{{#methods}}
    private doSend{{method.method_pascal_name}}({{#method.parameters}}{{#comma}}, {{/comma}}p{{parameter_name}}: {{parameter_type}}| undefined{{/method.parameters}}): void {
        if (this.mWebSocket !== undefined) {
            const data = {siid: this.mUuid, mthd: '{{method.method_name}}', prms: [ {{#method.parameters}}{{#comma}}, {{/comma}}{ {{parameter_name}}: p{{parameter_name}} }{{/method.parameters}} ], type: 1};
            this.mWebSocket.send(encode(data));
            console.log('Sending:' + JSON.stringify(data) + '.');
        }
    }


    public {{method.method_name}}({{#method.parameters}}{{#comma}}, {{/comma}}p{{parameter_name}}: {{parameter_type}}| undefined{{/method.parameters}}{{#method.pars_filled}},{{/method.pars_filled}} pReturn: {{method.method_pascal_name}}ReturnFunction): void {
        this.m{{method.method_pascal_name}}Return = pReturn;
        {{#method.parameters}}
        this.m{{parameter_name}}Par = p{{parameter_name}};
        console.log('{{parameter_name}}: "' + this.m{{parameter_name}}Par + '".');
        {{/method.parameters}}
        if (this.mUuid !== undefined && this.mUuid.length === 16) {
            this.doSend{{method.method_pascal_name}}({{#method.parameters}}{{#comma}}, {{/comma}}this.m{{parameter_name}}Par{{/method.parameters}});
        } else {
            this.retrieveUuid{{method.method_pascal_name}}();
        }
    }

    private onReceive{{method.method_pascal_name}}Uiid(p{{interface_name}}UuidResponse: {{interface_name}}UuidResponse): void {
        this.mUuid = p{{interface_name}}UuidResponse.svc.uuid_arr;
        console.log('UUID Response:' + this.mUuid);
        this.mWebSocket = new WebSocket('ws://' + this.mHostPortMods + '?upgrade');
        this.mWebSocket.onopen = () => { this.on{{method.method_pascal_name}}WsOpen(); };
        this.mWebSocket.onerror = (pError: any) => {
            console.log(`WebSocket error: ${pError}`);
        };
        this.mWebSocket.onclose = () => {
            console.log('Websocked closed');
            this.mUuid = new Uint8Array();
        };
        this.mWebSocket.onmessage = (pEvent: MessageEvent) => {this.onWsMessage(pEvent); };
    }

    private retrieveUuid{{method.method_pascal_name}}(): void {
        this.mHttp.get<{{interface_name}}UuidResponse>('http://' + this.mHostPortMods + '?svc')
            .subscribe((p{{interface_name}}UuidResponse: {{interface_name}}UuidResponse) => {this.onReceive{{method.method_pascal_name}}Uiid(p{{interface_name}}UuidResponse); },
                {{interface_name}}Service.onUiidReceiveError);
    }

{{/methods}}

    constructor(private mHttp: HttpClient, @Inject('mHostAndPort') private readonly mHostAndPort: string) {
        this.mHostPortMods = this.mHostAndPort + '/{{path}}';
        console.log('Created Striboh service: ' + this.mHostPortMods + '.');
    }
}
"""


def camel_to_snake(name: str):
    name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()


# Convert Snake case to Pascal case
# Using title() + replace()
def to_pascal_case(name: str):
    return name.replace("_", " ").title().replace(" ", "")


def idl_type_to_angular(p_type: striboh.EBuildInTypes):
    if p_type == striboh.EBuildInTypes.STRING:
        return 'string'
    if p_type == striboh.EBuildInTypes.INT:
        return 'number'
    if p_type == striboh.EBuildInTypes.FLOAT:
        return 'number'
    if p_type == striboh.EBuildInTypes.VOID:
        return 'void'
    raise Exception('Unknown type "{}"'.format(p_type))


class NgClientVisitor(NgVisitorBase, striboh.AstVisitor):
    m_filename: str
    m_method_index: int
    m_ast = {}
    m_modules = []

    def __init__(self):
        striboh.AstVisitor.__init__(self)
        NgVisitorBase.__init__(self)
        self.m_parameter_index = 0
        self.setRuns(1)
        self.m_run_no = 0
        logging.debug('NgClientVisitor::__init__')

    def getRuns(self) -> int:
        return 2

    def beginRun(self, p_run_no: int):
        logging.debug('NgClientVisitor::beginRun')

    def beginModule(self, p_module_name: str):
        logging.debug(f'NgClientVisitor::beginModule {p_module_name}')
        self.m_ast['module'] = p_module_name
        self.m_modules.append(p_module_name)

    def endModule(self, p_module_name):
        logging.debug('NgClientVisitor::endModule')

    def beginInterface(self, p_interface_name: str):
        logging.debug(f'NgClientVisitor::beginInterface {p_interface_name}')
        self.m_ast = {'interface_name': p_interface_name, 'methods': []}
        a_name = '{}.service.ts'.format(p_interface_name)
        self.m_filename = camel_to_snake(a_name)
        self.m_method_index = 0
        self.m_ast['path'] = '/'.join(self.m_modules) + '/' + p_interface_name;

    def endInterface(self, p_interface_name: str):
        logging.debug('NgClientVisitor::endInterface')
        self.addCode(self.m_filename, pystache.render(module_template, self.m_ast))

    def beginMethod(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgClientVisitor::beginMethod')
        self.m_parameter_index = 0
        self.m_ast['methods'].append({'method': {'method_name': p_identifier.getName(),
                                                 'method_pascal_name': to_pascal_case(p_identifier.getName()),
                                                 'method_type': idl_type_to_angular(p_identifier.getType()),
                                                 'parameters': []
                                                 }
                                      })

    def endMethod(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgClientVisitor::endMethod {}'.format(p_identifier.getName()))
        self.m_ast['methods'][self.m_method_index]['method']['pars_filled'] = (self.m_parameter_index>0)
        self.m_method_index += 1

    def beginParameter(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('NgClientVisitor::beginParameter')
        self.m_ast['methods'][self.m_method_index]['method']['parameters'] \
            .append({'parameter_name': to_pascal_case(p_identifier.getName()),
                     'parameter_type': idl_type_to_angular(p_identifier.getType()),
                     'comma': (self.m_parameter_index != 0)})
        self.m_parameter_index += 1


my_client_visitor = NgClientVisitor()
my_servant_visitor = NgServantVisitor()


def register():
    logging.info('Registering Angular backend.')
    striboh.setBackendVisitors(my_client_visitor, my_servant_visitor)
