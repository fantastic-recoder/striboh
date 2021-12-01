import sys
import logging

sys.path.append(['../lib', '../../../cmake-build-debug/lib'])

import stribohIdl


class CppVisitorBase:
    def __init__(self):
        logging.debug('CppVisitorBase::__init__')

class ServantVisitor(CppVisitorBase, stribohIdl.AstVisitor):
    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(2)
        logging.debug('ServantVisitor::__init__')

    def beginRun(self, p_run_num):
        logging.debug('ServantVisitor::beginRun')

    def beginModule(self, p_module_name):
        logging.debug('ServantVisitor::beginModule')

    def endModule(self, p_module_name):
        logging.debug('ServantVisitor::endModule')

    def beginInterface(self, p_interface_name):
        logging.debug('ServantVisitor::beginInterface')

    def endInterface(self, p_interface_name: str):
        logging.debug('ServantVisitor::endInterface')

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ServantVisitor::beginMethod')

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ServantVisitor::endMethod')

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ServantVisitor::beginParameter')

########################################################################################################################
# client visitor
########################################################################################################################

class ClientVisitor(CppVisitorBase, stribohIdl.AstVisitor):

    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(2)
        self.m_run_no = 0
        logging.debug('ClientVisitor::__init__')

    def getRuns(self) -> int:
        return 2

    def beginRun(self, p_run_no: int):
        logging.debug('ClientVisitor::beginRun')

    def beginModule(self, p_module_name: str):
        logging.debug('ClientVisitor::beginModule')

    def endModule(self, p_module_name):
        logging.debug('ClientVisitor::endModule')

    def beginInterface(self, p_interface_name: str):
        logging.debug('ClientVisitor::beginInterface')

    def endInterface(self, p_interface_name: stribohIdl.TypedIdentifierNode):
        logging.debug('ClientVisitor::endInterface')

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ClientVisitor::beginMethod')

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ClientVisitor::endMethod')

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        logging.debug('ClientVisitor::beginParameter')


my_client_visitor = ClientVisitor()
my_servant_visitor = ServantVisitor()


def register():
    logging.info('Registering Angular backend.')
    stribohIdl.setBackendVisitors(my_client_visitor, my_servant_visitor)
