import logging
import sys
import re
import pystache

sys.path.append(['../lib', '../../../cmake-build-debug/lib'])

import stribohIdl as striboh

def striboh_type_to_type_name(p_striboh_type: striboh.EBuildInTypes) -> str:
    if p_striboh_type == striboh.EBuildInTypes.STRING:
        return 'striboh::base::ETypes::K_STRING'
    if p_striboh_type == striboh.EBuildInTypes.INT:
        return "striboh::base::ETypes::K_INT"
    if p_striboh_type == striboh.EBuildInTypes.FLOAT:
        return "striboh::base::ETypes::K_FLOAT"
    raise RuntimeError('Unknown striboh type ' + p_striboh_type)


def striboh_type_to_cpp(p_striboh_type: striboh.EBuildInTypes) -> str:
    if p_striboh_type == striboh.EBuildInTypes.STRING:
        return "std::string"
    if p_striboh_type == striboh.EBuildInTypes.INT:
        return "int64_t"
    if p_striboh_type == striboh.EBuildInTypes.FLOAT:
        return "double"
    raise RuntimeError("Unknown striboh type {pStribohType}".format(pStribohType=p_striboh_type))


def striboh_type_to_cpp_par(p_striboh_type: striboh.EBuildInTypes)->str:
    if p_striboh_type == striboh.EBuildInTypes.STRING:
        return "std_string_ref"
    if p_striboh_type == striboh.EBuildInTypes.INT:
        return "int64_t"
    if p_striboh_type == striboh.EBuildInTypes.FLOAT:
        return "double"
    raise RuntimeError("Unknown striboh type {pStribohType}".format(pStribohType=p_striboh_type))


def camel_to_snake(name: str):
    name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).lower()


# Convert Snake case to Pascal case
# Using title() + replace()
def to_pascal_case(name: str):
    return name.replace("_", " ").title().replace(" ", "")


def concal_modules_to_comma_list(p_list: []):
    my_ret_val = []
    for ii in range(len(p_list)):
        my_ret_val.append({'mod': p_list[ii], 'comma': (ii>0)})
    return my_ret_val


class CppVisitorBase:
    m_run_no: int = 0
    m_module_depth: int = 0
    m_filename: str = 'unknown'
    m_include_guard: str
    m_ast = {}
    m_method_index = -7

    def __init__(self):
        self.__par_no = None
        self.m_modules = []

    def add_module(self,p_module_name: str):
        self.m_modules.append(p_module_name)
        self.m_ast['module'] = p_module_name
        self.m_module_depth += 1
        logging.debug('CppVisitorBase::begin_module: '+p_module_name)

    def end_module(self, p_module_name: str):
        self.m_module_depth -= 1
        del self.m_modules[-1]
        logging.debug('CppVisitorBase::end_module: '+p_module_name)

    def begin_interface(self, p_interface_name: str):
        self.m_ast = {'interface_name': p_interface_name, 'methods': []}
        a_name = '{}.service.ts'.format(p_interface_name)
        self.m_method_index = 0
        self.m_ast['path'] = '/'.join(self.m_modules) + '/' + p_interface_name
        self.m_ast['prefix'] = self.m_module_depth * '\t'
        self.m_ast['namespace'] = '::'.join(self.m_modules)
        self.m_ast['module_path'] = generate_module_path(self.m_modules)
        self.m_ast['modules_list'] = concal_modules_to_comma_list(self.m_modules)
        logging.debug(f'CppVisitorBase::begin_interface {p_interface_name}', p_interface_name)

    def end_interface(self, p_interface_name: str, p_module_template: str):
        logging.debug(f'CppVisitorBase::end_interface {p_interface_name}', p_interface_name)
        self.addCode(self.m_filename, pystache.render(p_module_template, self.m_ast))

    def begin_method(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('CppVisitorBase::begin_method')
        self.__par_no = 0
        self.m_ast['methods'].append({'method': {'method_name': p_identifier.getName(),
                                                 'method_pascal_name': to_pascal_case(p_identifier.getName()),
                                                 'method_type': striboh_type_to_cpp(p_identifier.getType()),
                                                 'parameters': [],
                                                 'not_first': self.m_method_index > 0
                                                 }
                                      })

    def end_method(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('CppVisitorBase::endMethod {}'.format(p_identifier.getName()))
        self.m_ast['methods'][self.m_method_index]['method']['pars_filled'] = (self.__par_no > 0)
        self.m_method_index += 1

    def add_parameter(self, p_identifier: striboh.TypedIdentifierNode):
        logging.debug('CppVisitorBase::beginParameter')
        self.m_ast['methods'][self.m_method_index]['method']['parameters']\
            .append({'parameter_name': to_pascal_case(p_identifier.getName()),
                     'parameter_type': striboh_type_to_cpp(p_identifier.getType()),
                     'parameter_type_ref': striboh_type_to_cpp_par(p_identifier.getType()),
                     'parameter_type_desc': striboh_type_to_type_name(p_identifier.getType()),
                     'parameter_idx': self.__par_no,
                     'comma': (self.__par_no != 0)})
        self.__par_no += 1

    def generate_namespace(self) -> str:
        my_ret_val: str = ''
        if len(self.m_modules) > 0:
            my_ret_val = "namespace "
        for ii in range(len(self.m_modules)):
            if ii > 0:
                my_ret_val += "::"
            my_ret_val += self.m_modules[ii]
        if len(self.m_modules) > 0:
            my_ret_val += " {\n"
        return my_ret_val

    def generate_namespace_closing(self):
        my_ret_val = ''
        if len(self.m_modules) > 0:
            my_ret_val = "} // end namespace \n";
        return my_ret_val

K_SERVANT_TEMPLATE = """
#pragma once

#include <string>
#include <vector>
#include <striboh/stribohBaseEMessageType.hpp>
#include <striboh/stribohBaseParameterList.hpp>
#include <striboh/stribohBaseMethod.hpp>
#include <striboh/stribohBaseMessage.hpp>
#include <striboh/stribohBaseInterface.hpp>
#include <striboh/stribohBaseServantBase.hpp>

namespace {{namespace}} {

     using std_string_ref =const std::string&;
     
	 class {{interface_name}} : public striboh::base::ServantBase {
	 public:

    {{#methods}}
		virtual {{method.method_type}} {{method.method_name}}({{#method.parameters}}{{#comma}}, {{/comma}}{{parameter_type_ref}} p{{parameter_name}}{{/method.parameters}}) = 0;
    {{/methods}}

	 	virtual const striboh::base::Interface& getInterface() const override { return mInterface; }

	 private:

	 striboh::base::Interface mInterface{
		*this,
		{ {{#modules_list}}{{#comma}},{{/comma}}"{{mod}}"{{/modules_list}} },
		striboh::base::InterfaceName{"{{interface_name}}"},
		{
            {{#methods}}
                {{#method.not_first}},{{/method.not_first}}
                striboh::base::Method{"{{method.method_name}}",
                    striboh::base::ParameterDescriptionList{
                        { {{#method.parameters}}
                            {{#comma}},
                            {{/comma}}striboh::base::ParameterDescription{striboh::base::EDirection::K_IN, {{parameter_type_desc}}, "{{parameter_name}}"}{{/method.parameters}}
                        }
                    },
                    [this](const striboh::base::Message &pIncoming,striboh::base::Context pCtx) {
                        auto myRetVal={{method.method_name}}({{#method.parameters}}
                            {{#comma}},
                            {{/comma}}pIncoming.getParameters()[{{parameter_idx}}].getValue().get<{{parameter_type}}>(){{/method.parameters}}
                        );
                        return striboh::base::Message(pIncoming,striboh::base::Value( myRetVal ),getLog());
                    },
                    getLog()
                }
            {{/methods}}
            } // end methods
		}; // end mInterface
	 }; // end interface {{interface_name}}
} // end namespace {{namespace}}
"""


class ServantVisitor(CppVisitorBase, striboh.AstVisitor):
    __lambda_parameter_list: str

    def __init__(self):
        striboh.AstVisitor.__init__(self)
        CppVisitorBase.__init__(self)
        self.setRuns(1)

    def beginRun(self, p_run_num):
        self.m_run_no = p_run_num

    def beginModule(self, p_module_name):
        self.add_module(p_module_name)

    def endModule(self, p_module_name):
        self.end_module(p_module_name)

    def beginInterface(self, p_interface_name):
        self.m_filename = '{}.hpp'.format(p_interface_name)
        self.begin_interface(p_interface_name)

    def endInterface(self, p_interface_name: str):
        self.end_interface(p_interface_name,K_SERVANT_TEMPLATE)

    def beginMethod(self, p_identifier: striboh.TypedIdentifierNode):
        self.begin_method(p_identifier)

    def endMethod(self, p_identifier: striboh.TypedIdentifierNode):
        self.end_method(p_identifier)

    def beginParameter(self, p_identifier: striboh.TypedIdentifierNode):
        self.add_parameter(p_identifier)


########################################################################################################################
# client visitor
########################################################################################################################
K_CLIENT_TEMPLATE = """
#pragma once
#include <string>
#include <vector>
#include <striboh/stribohBaseEMessageType.hpp>
#include <striboh/stribohBaseParameterList.hpp>
#include <striboh/stribohBaseMethod.hpp>
#include <striboh/stribohBaseMessage.hpp>
#include <striboh/stribohBaseInterface.hpp>
#include <striboh/stribohBaseProxyBase.hpp>
#include <striboh/stribohBaseBroker.hpp>
#include <striboh/stribohBaseAddress.hpp>

namespace {{namespace}} {
	class {{interface_name}}Proxy : public striboh::base::ProxyBase { // starting class {{interface_name}}Proxy
	public:
		{{interface_name}}Proxy(  std::string_view pUrl, striboh::base::LogIface& pLogIface )
			 : striboh::base::ProxyBase(striboh::base::Address(pUrl), "/{{module_path}}{{interface_name}}", pLogIface ) {}

        {{#methods}}
		 striboh::base::RetValProxy<{{method.method_type}}> {{method.method_name}}({{#method.parameters}}{{#comma}}, {{/comma}}{{parameter_type}} p{{parameter_name}}{{/method.parameters}}){
		 	striboh::base::Message {{method.method_name}}Msg("{{method.method_name}}", { {{#method.parameters}}{{#comma}},{{/comma}}{ "{{parameter_name}}", p{{parameter_name}} }{{/method.parameters}} }, getLog()); 
		 	// end method message
			return invoke(std::forward<striboh::base::Message>({{method.method_name}}Msg), {{method.method_type}}{} ); // send request
		 } // end method {{method.method_name}}

        {{/methods}}
	 };// end class {{interface_name}}
} // end namespace {{namespace}}

"""


def generate_module_path(p_module_names: [str]):
    my_module_path = ""
    for myModuleName in p_module_names:
        if len(my_module_path) == 0:
            my_module_path += myModuleName
        else:
            my_module_path += ("/" + myModuleName)
    if len(p_module_names) != 0:
        my_module_path += "/"
    return my_module_path


class ClientVisitor(CppVisitorBase, striboh.AstVisitor):
    __method_message_code: [str] = []
    __method_counter: int = 0

    def __init__(self):
        striboh.AstVisitor.__init__(self)
        CppVisitorBase.__init__(self)
        self.setRuns(1)
        self.m_run_no = 0

    def getRuns(self) -> int:
        return 2

    def beginRun(self, p_run_no: int):
        self.m_run_no = p_run_no;

    def beginModule(self, p_module_name: str):
        self.add_module(p_module_name)

    def endModule(self, p_module_name):
        self.end_module(p_module_name)

    def beginInterface(self, p_interface_name: str):
        self.m_filename = '{}Clt.hpp'.format(p_interface_name)
        self.begin_interface(p_interface_name)

    def endInterface(self, p_interface_name: str):
        self.end_interface(p_interface_name, K_CLIENT_TEMPLATE)

    def beginMethod(self, p_identifier: striboh.TypedIdentifierNode):
        self.begin_method(p_identifier)

    def endMethod(self, p_identifier: striboh.TypedIdentifierNode):
        self.end_method(p_identifier)

    def beginParameter(self, p_identifier: striboh.TypedIdentifierNode):
        self.add_parameter(p_identifier)


my_client_visitor = ClientVisitor()
my_servant_visitor = ServantVisitor()


def register():
    striboh.setBackendVisitors(my_client_visitor, my_servant_visitor)
