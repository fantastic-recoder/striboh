import sys

sys.path.append(['../lib', '../../../cmake-build-debug/lib'])

import stribohIdl


def striboh_type_to_type_name(p_striboh_type: str) -> str:
    if p_striboh_type == 'STRING':
        return 'striboh::base::ETypes::K_STRING'
    if p_striboh_type == "INT":
        return "striboh::base::ETypes::K_INT"
    raise RuntimeError('Unknown striboh type ' + p_striboh_type)


def striboh_type_to_cpp(p_striboh_type: str):
    if p_striboh_type == "STRING":
        return "std::string"
    if p_striboh_type == "INT":
        return "int64_t"
    raise RuntimeError("Unknown striboh type {pStribohType}".format(pStribohType=p_striboh_type))


def concat_string_list(p_list: []):
    my_ret_val = ''
    for ii in range(len(p_list)):
        if ii > 0:
            my_ret_val = my_ret_val + ','
        my_ret_val = my_ret_val + '"' + p_list[ii] + '"'
    return my_ret_val


class CppVisitorBase:
    m_run_no: int = 0
    m_module_names: [str] = []
    m_filename: str = 'unknown'
    m_include_guard: str

    def generate_namespace(self) -> str:
        my_ret_val: str = ''
        if len(self.m_module_names) > 0:
            my_ret_val = "namespace "
        for ii in range(len(self.m_module_names)):
            if ii > 0:
                my_ret_val += "::"
            my_ret_val += self.m_module_names[ii]
        if len(self.m_module_names) > 0:
            my_ret_val += " {\n"
        return my_ret_val

    def generate_namespace_closing(self):
        my_ret_val = ''
        if len(self.m_module_names) > 0:
            my_ret_val = "} // end namespace \n";
        return my_ret_val


SERVANT_BASE_HPP_: str = """
#ifndef {theIncludeGuard}
#define {theIncludeGuard}

#include <string>
#include <vector>
#include <striboh/stribohBaseEMessageType.hpp>
#include <striboh/stribohBaseParameterList.hpp>
#include <striboh/stribohBaseMethod.hpp>
#include <striboh/stribohBaseMessage.hpp>
#include <striboh/stribohBaseInterface.hpp>
#include <striboh/stribohBaseServantBase.hpp>
"""

SERVANT_PARAMETER_DESC_LIST = """
{myPrefix}\t\tstriboh::base::Method{{"{pMethodName}",
{myPrefix}\t\t\tstriboh::base::ParameterDescriptionList{{
{myPrefix}\t\t\t\t{{
"""

SERVANT_CLOSE_METHOD = """
{myPrefix}\t\t\t\t}}
{myPrefix}\t\t\t}},
{myPrefix}\t\t\t[this](const striboh::base::Message &pIncoming,striboh::base::Context pCtx) {{
{myPrefix}\t\t\t\tauto myRetVal={pMethodName}(\n{theLambdaParameterList}
{myPrefix}\t\t\t\t);
{myPrefix}\t\t\t\treturn striboh::base::Message(striboh::base::Value( myRetVal ),getLog());
{myPrefix}\t\t\t}},
{myPrefix}\t\t\tgetLog()
{myPrefix}\t\t}} // end servant method
"""

SERVANT_HEAD_: str = """
{myPrefix}virtual const striboh::base::Interface& getInterface() const override {{ return mInterface; }}

{myPrefix}private:

{myPrefix}striboh::base::Interface mInterface{{
{myPrefix}\t*this,
{myPrefix}\t{{ {myModuleList} }},
{myPrefix}\tstriboh::base::InterfaceName{{"{pInterfaceName}"}},
{myPrefix}\t{{"""

SERVANT_END_INTERFACE = """
{myPrefix}\t}} // end methods init list
{myPrefix}}}; // end Interface definition

{myPrefix}}}; // end servant

}} // end namespace
#endif // {theIncludeGuard}
"""


class ServantVisitor(CppVisitorBase, stribohIdl.AstVisitor):
    __module_depth: int = 0
    __module_code_begin: str = ""
    __method_no: int = 0
    __par_no = -1
    __lambda_parameter_list: str

    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(2)

    def beginRun(self, p_run_num):
        self.m_run_no = p_run_num

    def beginModule(self, p_module_name):
        self.m_module_names.append(p_module_name)
        self.__module_depth += 1

    def endModule(self, p_module_name):
        self.__module_depth -= 1
        del self.m_module_names[-1]

    def beginInterface(self, p_interface_name):
        self.__method_no = 0
        self.m_include_guard = "{pInterfaceName}_SERVANT_GUARD_HPP".format(pInterfaceName=p_interface_name)
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 1:
            my_header_code = SERVANT_BASE_HPP_.format(theIncludeGuard=self.m_include_guard)
            self.m_filename = '{}.hpp'.format(p_interface_name)
            self.addCode(self.m_filename, my_header_code);
            self.addCode(self.m_filename, self.generate_namespace());
            self.addCode(self.m_filename, '{myPrefix} class {pInterfaceName} : public striboh::base::ServantBase {{\n'
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.m_filename, '{} public:\n'.format(my_prefix))

        if self.m_run_no == 2:
            my_module_list = concat_string_list(self.m_module_names)
            # print('Module list:{}'.format(my_module_list))
            self.addCode(self.m_filename, SERVANT_HEAD_.format(myPrefix=my_prefix, myModuleList=my_module_list,
                                                               pInterfaceName=p_interface_name))

    def endInterface(self, p_interface_name: str):
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 2:
            self.addCode(self.m_filename,
                         SERVANT_END_INTERFACE.format(myPrefix=my_prefix, theIncludeGuard=self.m_include_guard))

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        self.__par_no = 0
        self.__lambda_parameter_list = ""
        if self.m_run_no == 1:
            my_prefix = self.__module_depth * '\t'
            my_cpp_type = striboh_type_to_cpp(p_identifier.getTypeString())
            self.addCode(self.m_filename, '\n{myPrefix}virtual {myCppType} {pMethodName}('
                         .format(myPrefix=my_prefix, myCppType=my_cpp_type, pMethodName=p_identifier.getName()));
        if self.m_run_no == 2:
            my_prefix = self.__module_depth * '\t'
            if self.__method_no > 0:
                self.addCode(self.m_filename, "{myPrefix}\t\t,".format(myPrefix=my_prefix))
            self.addCode(self.m_filename,
                         SERVANT_PARAMETER_DESC_LIST.format(myPrefix=my_prefix, pMethodName=p_identifier.getName()))

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        if self.m_run_no == 1:
            self.addCode(self.m_filename, " ) = 0;\n")
        if self.m_run_no == 2:
            my_prefix = self.__module_depth * '\t'
            self.addCode(self.m_filename,
                         SERVANT_CLOSE_METHOD.format(myPrefix=my_prefix, pMethodName=p_identifier.getName(),
                                                     theLambdaParameterList=self.__lambda_parameter_list))
        self.__method_no += 1

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        my_cpp_type = striboh_type_to_cpp(p_identifier.getTypeString())
        if self.m_run_no == 1:
            if self.__par_no > 0:
                self.addCode(self.m_filename, ", ")
            self.addCode(self.m_filename, "const {myCppType} & {pParameterName}"
                         .format(myCppType=my_cpp_type, pParameterName=p_identifier.getName()))
        if self.m_run_no == 2:
            my_prefix = (self.__module_depth + 1) * '\t'
            my_parameter_type_name = striboh_type_to_type_name(p_identifier.getTypeString())
            if self.__par_no > 0:  # add colon
                self.__lambda_parameter_list += ",\n"
                self.addCode(self.m_filename, "\n{myPrefix}\t\t\t,\n".format(myPrefix=my_prefix))
            self.__lambda_parameter_list \
                += '{myPrefix}\t\t\tpIncoming.getParameters()[{theParNo}].getValue().get<{myCppType}>()' \
                .format(myPrefix=my_prefix, theParNo=self.__par_no, myCppType=my_cpp_type)
            self.addCode(self.m_filename,
                         "{myPrefix}\t\t\tstriboh::base::ParameterDescription{{striboh::base::EDirection::K_IN, {myParameterTypeName}, \"{pParameterName}\"}}"
                         .format(myPrefix=my_prefix, myParameterTypeName=my_parameter_type_name,
                                 pParameterName=p_identifier.getName()))
        self.__par_no = self.__par_no + 1


########################################################################################################################
# client visitor
########################################################################################################################

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


class ClientVisitor(CppVisitorBase, stribohIdl.AstVisitor):
    __method_message_code: [str] = []
    __method_counter: int = 0
    __par_no: int = -1;
    __module_depth: int = 0;

    def __init__(self):
        stribohIdl.AstVisitor.__init__(self)
        self.setRuns(2)
        self.m_run_no = 0

    def getRuns(self) -> int:
        return 2

    def beginRun(self, p_run_no: int):
        self.m_run_no = p_run_no;

    def beginModule(self, p_module_name: str):
        self.m_module_names.append(p_module_name)

    def endModule(self, p_module_name):
        del self.m_module_names[-1]

    def beginInterface(self, p_interface_name: str):
        self.m_include_guard = "{pInterfaceName}_CLIENT_GUARD_HPP".format(pInterfaceName=p_interface_name)
        my_prefix = self.__module_depth * '\t'
        self.__method_counter = 0
        if self.m_run_no == 1:
            self.__method_message_code.clear()
            self.m_filename = "{pInterfaceName}Clt.hpp".format(pInterfaceName=p_interface_name)
        if self.m_run_no == 2:
            self.addCode(self.m_filename, "#ifndef {theIncludeGuard}\n".format(theIncludeGuard=self.m_include_guard))
            self.addCode(self.m_filename, "#define {theIncludeGuard}\n".format(theIncludeGuard=self.m_include_guard))
            self.addCode(self.m_filename, "#include <string>\n")
            self.addCode(self.m_filename, "#include <vector>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseEMessageType.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseParameterList.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseMethod.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseMessage.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseInterface.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseProxyBase.hpp>\n")
            self.addCode(self.m_filename, "#include <striboh/stribohBaseBroker.hpp>\n")
            self.addCode(self.m_filename, "\n")
            self.addCode(self.m_filename, self.generate_namespace())
            my_module_path = generate_module_path(self.m_module_names)
            self.addCode(self.m_filename,
                         '{myPrefix}\tclass {pInterfaceName}Proxy : public striboh::base::ProxyBase {{ '
                         '// starting class {pInterfaceName}Proxy\n'
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.m_filename, "{myPrefix}\tpublic:\n".format(myPrefix=my_prefix));
            self.addCode(self.m_filename, "{myPrefix}\t\t{pInterfaceName}Proxy(  std::string_view pHost, short pPort,"
                                          " striboh::base::LogIface& pLogIface )\n"
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.m_filename, '{myPrefix}\t\t\t : striboh::base::ProxyBase(pHost, pPort, '
                                          '"/{myModulePath}{pInterfaceName}", pLogIface ) {{}}\n'
                         .format(myPrefix=my_prefix, myModulePath=my_module_path, pInterfaceName=p_interface_name))
        self.__module_depth += 1

    def endInterface(self, p_interface_name: str):
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 2:
            self.addCode(self.m_filename, "{myPrefix} }};// end class {pInterfaceName}\n"
                         .format(myPrefix=my_prefix,
                                 pInterfaceName=p_interface_name))
            self.addCode(self.m_filename, self.generate_namespace_closing())
            self.addCode(self.m_filename, "#endif // {includeGuard}\n".format(includeGuard=self.m_include_guard))
        self.__module_depth -= 1

    def beginMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        my_method_type = striboh_type_to_cpp(p_identifier.getTypeString())
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 1:
            self.__par_no = 0
            self.__method_message_code.append(
                '{myPrefix}\tstriboh::base::Message {pMethodName}Msg("{pMethodName}", {{\n'
                    .format(myPrefix=my_prefix, pMethodName=p_identifier.getName(), myMethodType=my_method_type))
        if self.m_run_no == 2:
            self.__par_no = 0
            self.addCode(self.m_filename,
                         "\n{myPrefix}\t striboh::base::RetValProxy<{myMethodType}> {pMethodName}("
                         .format(myPrefix=my_prefix, pMethodName=p_identifier.getName(), myMethodType=my_method_type))

    def endMethod(self, p_identifier: stribohIdl.TypedIdentifierNode):
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 1:
            self.__method_message_code[self.__method_counter] += (
                "\n{myPrefix}\t\t }} , getLog() ); // end method message"
                .format(myPrefix=my_prefix))
        if self.m_run_no == 2:
            my_cpp_type = striboh_type_to_cpp(p_identifier.getTypeString())
            self.addCode(self.m_filename, "){\n")
            self.addCode(self.m_filename, "{myPrefix}\t {my_method_message}\n"
                         .format(myPrefix=my_prefix,
                                 my_method_message=self.__method_message_code[self.__method_counter]))
            self.addCode(self.m_filename, "{myPrefix}\t\t return invoke("
                                          "std::forward<striboh::base::Message>({pMethodName}Msg), {myCppType}{{}} );"
                                          " // send request\n"
                         .format(myPrefix=my_prefix, pMethodName=p_identifier.getName(),
                                 myCppType=striboh_type_to_cpp(p_identifier.getTypeString())))
            self.addCode(self.m_filename, "{myPrefix}\t }} // end method\n".format(myPrefix=my_prefix))
        self.__method_counter += 1

    def beginParameter(self, p_identifier: stribohIdl.TypedIdentifierNode):
        my_parameter_type = striboh_type_to_cpp(p_identifier.getTypeString())
        my_prefix = self.__module_depth * '\t'
        if self.m_run_no == 1:
            if self.__par_no == 0:
                self.__method_message_code[
                    self.__method_counter] += "{myPrefix}\t\t\t{{ \"{pParameterName}\", {pParameterName} }}" \
                    .format(myParameterType=my_parameter_type, pParameterName=p_identifier.getName(),
                            myPrefix=my_prefix)
            else:
                self.__method_message_code[
                    self.__method_counter] += ",\n{myPrefix}\t\t\t{{ \"{pParameterName}\", {pParameterName} }}" \
                    .format(myParameterType=my_parameter_type, pParameterName=p_identifier.getName(),
                            myPrefix=my_prefix)
            self.__par_no += 1
        if self.m_run_no == 2:
            if self.__par_no > 0:
                self.addCode(self.m_filename, ", ")
            self.addCode(self.m_filename, "{myParameterType} {pParameterName}"
                         .format(myParameterType=my_parameter_type, pParameterName=p_identifier.getName()))
        self.__par_no += 1


my_client_visitor = ClientVisitor()
my_servant_visitor = ServantVisitor()


def register():
    stribohIdl.setBackendVisitors(my_client_visitor, my_servant_visitor)
