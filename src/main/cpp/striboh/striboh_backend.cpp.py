import sys

sys.path.append('../lib', '../../../cmake-build-debug/lib')
import stribohIdl

theIncludeGuard = 'K_ECHO_SERVANT_GUARD_HPP'


def concat_prefix(p_depth: int) -> str:
    my_prefix: str = ''
    for ii in range(p_depth):
        my_prefix = my_prefix + '\t'
    return my_prefix


def striboh_type_to_TypeName(p_striboh_type: str) -> str:
    if p_striboh_type == 'STRING':
        return 'striboh::base::ETypes::K_STRING'
    if p_striboh_type == "INT":
        return "striboh::base::ETypes::K_INT"
    raise RuntimeError('Unknown striboh type ' + p_striboh_type)


def striboh_type_to_cpp(p_striboh_type):
    if p_striboh_type == "STRING":
        return "std::string"
    if p_striboh_type == "INT":
        return "int64_t"
    raise RuntimeError("Unknown striboh type ${pStribohType}".format(pStribohType=p_striboh_type))


def concat_string_list(p_list: []):
    my_ret_val = ''
    for ii in range(p_list.size()):
        if ii > 0:
            my_ret_val = my_ret_val + ','
        my_ret_val = my_ret_val + '"' + p_list[ii] + '"'
    return my_ret_val


class ServantVisitor(stribohIdl.PyAstVisitor):
    __the_run_no: int = 0
    __header_code: str = ""
    __module_depth: int = 0
    __module_names: [str] = []
    __module_code_begin: str = ""
    __method_no: int = 0
    __filename = 'unknown'
    __par_no = -1
    __lambda_parameter_list: str

    def generate_namespace(self, pInterfaceName):
        if len(self.__module_names) == 0:
            self.addCode(self.__filename, "namespace ")
        for ii in range(len(self.__module_names)):
            if ii > 0:
                self.addCode(self.__filename, "::")
            my_namespace = self.__module_names[ii]
            self.addCode(self.__filename, my_namespace)
        if len(self.__module_names) == 0:
            self.addCode(self.__filename, " {\n")

    def generate_namespace_closing(self):
        if len(self.__module_names) > 0:
            self.addCode(self.__filename, "} // end namespace \n")

    def __init__(self):
        stribohIdl.stribohIdlSetRuns(2)  # set tree visitor runs

    def beginRun(self, p_run_num):
        self.__the_run_no = p_run_num

    def stribohIdlServantBeginModule(self, pModuleName):
        self.__module_names.append(pModuleName)
        self.__module_depth += 1

    def stribohIdlServantEndModule(self, p_module_name):
        self.__module_depth += 1
        del self.__module_names[-1]

    def beginInterface(self, p_interface_name):
        self.__method_no = 0
        self.__include_guard = "${pInterfaceName}_SERVANT_GUARD_HPP".format(pInterfaceName=p_interface_name)
        if self.__the_run_no == 1:
            self.__header_code += """#ifndef ${theIncludeGuard}
#define ${theIncludeGuard}
#include <string>
#include <vector>
#include <striboh/stribohBaseEMessageType.hpp>
#include <striboh/stribohBaseParameterList.hpp>
#include <striboh/stribohBaseMethod.hpp>
#include <striboh/stribohBaseMessage.hpp>
#include <striboh/stribohBaseInterface.hpp>
#include <striboh/stribohBaseServantBase.hpp>\n
""".format(theIncludeGuard=self.__include_guard)
        my_prefix = concat_prefix(self.__module_depth)
        if self.__the_run_no == 1:
            self.__filename = '{}.hpp'.format(p_interface_name)
            self.addCode(self.__filename, self.__header_code);
            self.generate_namespace(p_interface_name);
            self.addCode(self.__filename, '{myPrefix} class {pInterfaceName} : public striboh::base::ServantBase {\n'
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.__filename, '{} public:\n'.format(my_prefix))
        if self.__the_run_no == 2:
            my_module_list = concat_string_list(self.__module_names)
            print('Module list:{}'.format(my_module_list))
            self.addCode(self.__filename, """
{myPrefix}\t virtual const striboh::base::Interface& getInterface() const override { return mInterface; }

{myPrefix} private:
{myPrefix}\t striboh::base::Interface mInterface{
{myPrefix}\t\t *this
{myPrefix}\t\t { {myModuleList} }
{myPrefix}\t\t striboh::base::InterfaceName{"{pInterfaceName}"}
{myPrefix}\t\t {""".format(myPrefix=my_prefix, myModuleList=my_module_list, pInterfaceName=p_interface_name))
        self.__module_depth += 1

    def endInterface(self, pInterfaceName):
        self.__module_depth += 1
        my_prefix = concat_prefix(self.__module_depth);
        if self.__the_run_no == 2:
            self.addCode(self.__filename, """${myPrefix}\t\t }
${myPrefix}\t }

${myPrefix}};
\n} // end namespace
#endif // ${theIncludeGuard}
""".format(myPrefix=my_prefix, theIncludeGuard=self.__include_guard))

    def beginMethod(self, p_method_name, p_return_type):
        self.__par_no = 0
        self.__lambda_parameter_list = ""
        if self.__the_run_no == 1:
            my_prefix = concat_prefix(self.__module_depth)
            my_cpp_type = striboh_type_to_cpp(p_return_type)
            self.addCode(self.__filename, '\n{myPrefix} virtual {myCppType} {pMethodName}('
                         .format(myPrefix=my_prefix, myCppType=my_cpp_type, pMethodName=p_method_name));
        if self.__the_run_no == 2:
            my_prefix = concat_prefix(self.__module_depth + 1)
            if self.__method_no > 0:
                self.addCode(self.__filename, "${myPrefix}\t ,\n".format(myPrefix=my_prefix))
            self.addCode(self.__filename, """{myPrefix}\t striboh::base::Method{\"${pMethodName}\",
{myPrefix}\t\t striboh::base::ParameterDescriptionList{
{myPrefix}\t\t\t {
""".format(myPrefix=my_prefix, pMethodName=p_method_name))

    def endMethod(self, pMethodName, pMethodType):
        if self.__the_run_no == 1:
            self.addCode(self.__filename, " ) = 0;\n")
        if self.__the_run_no == 2:
            my_prefix = concat_prefix(self.__module_depth + 1)
            self.addCode(self.__filename, """${myPrefix}\t\t\t }
"${myPrefix}\t\t },
"${myPrefix}\t\t [this](const striboh::base::Message &pIncoming,striboh::base::Context pCtx) {
"${myPrefix}\t\t\t auto myRetVal={pMethodName}({theLambdaParameterList});
"${myPrefix}\t\t\t );
"${myPrefix}\t\t\t return striboh::base::Message(striboh::base::Value( myRetVal ),getLog());
"${myPrefix}\t\t },
"${myPrefix}\t\t getLog()
"${myPrefix}\t }
""".format(myPrefix=my_prefix, pMethodName=pMethodName, theLambdaParameterList=self.__lambda_parameter_list))
        self.__method_no += 1

    def beginParameter(self, pParameterName, pType):
        my_cpp_type = striboh_type_to_cpp(pType)
        if self.__the_run_no == 1:
            if self.__par_no > 0:
                self.addCode(self.__filename, ", ")
            self.addCode(self.__filename, "const ${myCppType} & ${pParameterName}"
                         .format(myCppType=my_cpp_type, pParameterName=pParameterName))
        if self.__the_run_no == 2:
            my_prefix = concat_prefix(self.__module_depth + 1)
            my_parameter_type_name = striboh_type_to_TypeName(pType)
            if self.__par_no > 0:
                self.__lambda_parameter_list += "${myPrefix}\t\t\t ,\n".format(myPrefix=my_prefix)
            self.addCode(self.__filename, "${myPrefix}\t\t\t\t\t ,\n".format(myPrefix=my_prefix))
            self.__lambda_parameter_list += "${myPrefix}\t\t\t pIncoming.getParameters()[${theParNo}].getValue().get<${myCppType}>()\n" \
                .format(myPrefix=my_prefix, theParNo=self.__par_no, myCppType=my_cpp_type)
            self.addCode(self.__filename,
                         "${myPrefix}\t\t\t\t\t striboh::base::ParameterDescription{striboh::base::EDirection::K_IN, ${myParameterTypeName}, \"${pParameterName}\"}\n"
                         .format(myPrefix=my_prefix, myParameterTypeName=my_parameter_type_name,
                                 pParameterName=pParameterName))
        self.__par_no = self.__par_no + 1


#################### client visitor

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


class ClientVisitor(stribohIdl.PyAstVisitor):
    __include_guard: str
    __module_names: [str] = []
    __method_message_code: [str] = []
    __method_counter: int = 0
    __run_no: int = 0
    __par_no: int = -1;

    def __init__(self):
        self.__run_no = 0
        stribohIdl.stribohIdlSetRuns(2)  # set tree visitor runs

    def beginRun(self, pRunNo: int):
        self.__run_no = self.__run_no + 1

    def beginModule(self, p_module_name):
        self.__module_names.append(p_module_name)

    def endModule(self, p_module_name):
        del self.__module_names[-1]

    def beginInterface(self, p_interface_name: str):
        self.__include_guard = "${pInterfaceName}_CLIENT_GUARD_HPP".format(pInterfaceName=p_interface_name)
        my_prefix = concat_prefix(self.theModuleDepth)
        self.__method_counter = 0
        if self.__run_no == 1:
            self.__method_message_code.clear()
            self.__filename = "${pInterfaceName}Clt.hpp".format(pInterfaceName=p_interface_name)
        if self.__run_no == 2:
            self.addCode(self.__filename, "#ifndef ${theIncludeGuard}\n".format(theIncludeGuard=self.__include_guard))
            self.addCode(self.__filename, "#define ${theIncludeGuard}\n".format(theIncludeGuard=self.__include_guard))
            self.addCode(self.__filename, "#include <string>\n")
            self.addCode(self.__filename, "#include <vector>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseEMessageType.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseParameterList.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseMethod.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseMessage.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseInterface.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseProxyBase.hpp>\n")
            self.addCode(self.__filename, "#include <striboh/stribohBaseBroker.hpp>\n")
            self.addCode(self.__filename, "\n")
            self.generateNamespace(p_interface_name)
            my_module_path = generate_module_path(self.__module_names)
            self.addCode(self.__filename,
                         "{myPrefix}\t class ${pInterfaceName}Proxy : public striboh::base::ProxyBase {\n\");"
                         "// starting class ${pInterfaceName}Proxy\n"
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.__filename, "{myPrefix}\t public:\n".format(myPrefix=my_prefix));
            self.addCode(self.__filename, "{myPrefix}\t\t ${pInterfaceName}Proxy(  std::string_view pHost, short pPort,"
                                          " striboh::base::LogIface& pLogIface )\n"
                         .format(myPrefix=my_prefix, pInterfaceName=p_interface_name))
            self.addCode(self.__filename, '{myPrefix}\t\t\t : striboh::base::ProxyBase(pHost, pPort, '
                                          '"/{myModulePath}{pInterfaceName}", pLogIface ) {}\n'
                         .format(myPrefix=my_prefix, myModulePath=my_module_path, pInterfaceName=p_interface_name))
        self.theModuleDepth += 1

    def stribohIdlClientEndInterface(self, p_interface_name):
        my_prefix = concat_prefix(self.theModuleDepth)
        if self.__run_no == 2:
            self.addCode(self.__filename, "${myPrefix} };// end class ${pInterfaceName}\n".format(myPrefix=my_prefix,
                                                                                                  pInterfaceName=p_interface_name))
            self.generateNamespaceClosing()
            self.addCode(self.__filename, "#endif // ${theIncludeGuard}\n".format(theIncludeGuard=self.__include_guard))
        self.theModuleDepth -= 1

    def stribohIdlClientBeginMethod(self, pMethodName, pReturnType):
        myMethodType = striboh_type_to_cpp(pReturnType)
        myPrefix = concat_prefix(self.theModuleDepth)
        if self.__run_no == 1:
            self.__par_no = 0
            self.__method_message_code.append(
                "{myPrefix} striboh::base::Message {pMethodName}Msg(\"{pMethodName}\", {\n".format(myPrefix=myPrefix,
                                                                                                   pMethodName=pMethodName,
                                                                                                   myMethodType=myMethodType))
        if self.__run_no == 2:
            self.__par_no = 0
            self.addCode(self.__filename,
                         "{myPrefix}\t striboh::base::RetValProxy<{myMethodType}> {pMethodName}(".format(
                             myPrefix=myPrefix, pMethodName=pMethodName, myMethodType=myMethodType))

    def stribohIdlClientEndMethod(self, p_method_name, p_return_type):
        my_prefix = concat_prefix(self.theModuleDepth)
        if self.__run_no == 1:
            self.__method_message_code[self.__method_counter].append(
                "\n{myPrefix}\t\t } , getLog() ); // end method message".format(myPrefix=my_prefix))
        if self.__run_no == 2:
            my_cpp_type = striboh_type_to_cpp(p_return_type)
            self.addCode(self.__filename, "){\n")
            self.addCode(self.__filename, "{myPrefix}\t {my_method_message}\n"
                         .format(myPrefix=my_prefix,
                                 my_method_message=self.__method_message_code[self.__method_counter]))
            self.addCode(self.__filename, "{myPrefix}\t\t return invoke("
                                          "std::forward<striboh::base::Message>({pMethodName}Msg), {myCppType}{} );"
                                          " // send request\n"
                         .format(myPrefix=my_prefix, pMethodName=p_method_name, myCppType=my_cpp_type))
            self.addCode(self.__filename, "{myPrefix}\t } // end method\n".format(myPrefix=my_prefix))
        self.__method_counter += 1

    def stribohIdlClientBeginParameter(self, p_parameter_name, p_parameter_type):
        my_parameter_type = striboh_type_to_cpp(p_parameter_type)
        my_prefix = concat_prefix(self.theModuleDepth)
        if self.__run_no == 1:
            if self.__par_no == 0:
                self.__method_message_code[
                    self.__method_counter] += "${myPrefix}\t\t\t{ \"${pParameterName}\", ${pParameterName} }" \
                    .format(myParameterType=my_parameter_type, pParameterName=p_parameter_name, myPrefix=my_prefix)
            else:
                self.__method_message_code[
                    self.__method_counter] += ",\n${myPrefix}\t\t\t{ \"${pParameterName}\", ${pParameterName} }" \
                    .format(myParameterType=my_parameter_type, pParameterName=p_parameter_name, myPrefix=my_prefix)
            self.__par_no += 1
        if self.__run_no == 2:
            if self.__par_no > 0:
                self.addCode(self.__filename, ", ")
                self.addCode(self.__filename, "${myParameterType} ${pParameterName}"
                             .format(myParameterType=my_parameter_type, pParameterName=p_parameter_name))
        self.__par_no += 1
