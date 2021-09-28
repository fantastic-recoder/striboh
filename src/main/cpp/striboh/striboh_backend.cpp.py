import sys
sys.path.append('../lib','../../../cmake-build-debug/lib')
import stribohIdl

theIncludeGuard = 'K_ECHO_SERVANT_GUARD_HPP'

def concat_prefix(p_depth:int) -> str:
    my_prefix: str= ''
    for ii in range(p_depth):
        my_prefix= my_prefix + '\t'
    return my_prefix

def striboh_type_to_TypeName(p_striboh_type:str) ->str:
    if p_striboh_type == 'STRING':
        return 'striboh::base::ETypes::K_STRING'
    if p_striboh_type == "INT" :
        return "striboh::base::ETypes::K_INT"
    raise RuntimeError('Unknown striboh type ' + p_striboh_type)

def striboh_type_to_cpp(p_striboh_type):
    if p_striboh_type == "STRING":
        return "std::string"
    if p_striboh_type == "INT"
        return "int64_t"
    raise RuntimeError("Unknown striboh type ${pStribohType}")

def concat_string_list(p_list:[]):
    my_ret_val= ''
    for ii in range(p_list.size()):
        if ii > 0 :
            my_ret_val=my_ret_val+','
        my_ret_val= my_ret_val +'"' + p_list[ii] + '"'
    return my_ret_val

class ServantVisitor(stribohIdl.PyAstVisitor):
    __the_run_no__=0
    theHeaderCode = ""

    def __init__(self):
            stribohIdl.stribohIdlSetRuns(2) # set tree visitor runs

    def beginRun(self, pRunNum):
       self.__the_run_no__ += 1
       if self.__the_run_no__==1 :
           self.theHeaderCode += """#ifndef {theIncludeGuard}
            #define {theIncludeGuard}
            #include <string>
            #include <vector>
            #include <striboh/stribohBaseEMessageType.hpp>
            #include <striboh/stribohBaseParameterList.hpp>
            #include <striboh/stribohBaseMethod.hpp>
            #include <striboh/stribohBaseMessage.hpp>
            #include <striboh/stribohBaseInterface.hpp>
            #include <striboh/stribohBaseServantBase.hpp>
            """.format(theIncludeGuard=self.theIncludeGuard)

    theModuleDepth = 0
    theModuleNames = []
    theModuleCodeBegin = ""

    def generateNamespace(self, pInterfaceName):
        if len(self.theModuleNames)==0 :
            self.addCode(theFilename, "namespace ")
        for ii in range(len(self.theModuleNames)) :
            if ii>0 :
                self.addCode(self.theFilename, "::")
            myNamespace=self.theModuleNames[ii]
            self.addCode(theFilename, myNamespace)
        if len(self.theModuleNames)==0 :
            self.addCode(self.theFilename, " {\n")

    def generateNamespaceClosing(self):
        if len(self.theModuleNames)>0 :
            self.addCode(theFilename, "} // end namespace \n")

    def stribohIdlServantBeginModule(self,pModuleName):
       self.theModuleNames.append(pModuleName)
       self.theModuleDepth += 1

    def stribohIdlServantEndModule(self,pModuleName)
       self.theModuleDepth += 1
       del self.theModuleNames[-1]

    theMethodNo:int = 0
    theFilename = 'unknown'

    def beginInterface(self,pInterfaceName):
        self.theMethodNo = 0
        myPrefix=concat_prefix(self.theModuleDepth)
        if self.__the_run_no__==1 :
           self.theFilename = '{}.hpp'.format(pInterfaceName)
           self.addCode(self.theFilename, theHeaderCode);
           generateNamespace(pInterfaceName);
           self.addCode(self.theFilename, '{myPrefix} class {pInterfaceName} : public striboh::base::ServantBase {\n'
                        .format(myPrefix=myPrefix,pInterfaceName=pInterfaceName))
           self.addCode(self.theFilename, '{} public:\n'.format(myPrefix))
        if __the_run_no__==2 :
           myModuleList = concat_string_list()
           print('Module list:${}'.format(myModuleList))
           self.addCode(self.theFilename, """
            {myPrefix}\t virtual const striboh::base::Interface& getInterface() const override { return mInterface; }
            
            {myPrefix} private:
            {myPrefix}\t striboh::base::Interface mInterface{
            {myPrefix}\t\t *this
            {myPrefix}\t\t { {myModuleList} }
            {myPrefix}\t\t striboh::base::InterfaceName{"{pInterfaceName}"}
            {myPrefix}\t\t {""".format(myPrefix=myPrefix,myModuleList=myModuleList,pInterfaceName=pInterfaceName))
        self.theModuleDepth += 1

    def endInterface(self,pInterfaceName):
       self.theModuleDepth += 1
       myPrefix=concat_prefix(self.theModuleDepth);
       if __the_run_no__ == 2 :
           self.addCode(self.theFilename, """${myPrefix}\t\t }
            ${myPrefix}\t }
            
            ${myPrefix}};
            \n} // end namespace
            #endif // ${theIncludeGuard}
            """.format(myPrefix=myPrefix))

    theParNo = -1
    theLambdaParameterList: str

    def beginMethod(self,pMethodName,pReturnType):
       self.theParNo = 0
       self.theLambdaParameterList = ""
       if self.__the_run_no__==1 :
           myPrefix=concat_prefix(self.theModuleDepth)
           myCppType=striboh_type_to_cpp(pReturnType)
           self.addCode(theFilename, '\n{myPrefix} virtual {myCppType} {pMethodName}('
                        .format(myPrefix=myPrefix,myCppType=myCppType,pMethodName=pMethodName));
       if __the_run_no__==2 :
           myPrefix=concat_prefix(self.theModuleDepth+1)
           if theMethodNo>0 :
               addCode(theFilename, "${myPrefix}\t ,\n");
           }
           addCode(theFilename, """{myPrefix}\t striboh::base::Method{\"${pMethodName}\",
{myPrefix}\t\t striboh::base::ParameterDescriptionList{
{myPrefix}\t\t\t {
""".format(myPrefix=myPrefix))

    def stribohIdlServantEndMethod(self,pMethodName,pMethodType):
       if __the_run_no__==1 :
           self.addCode(theFilename, " ) = 0;\n");
       if __the_run_no__==2 :
          myPrefix=concat_prefix(theModuleDepth+1);
          self.addCode(self.theFilename, """${myPrefix}\t\t\t }
            "${myPrefix}\t\t },
            "${myPrefix}\t\t [this](const striboh::base::Message &pIncoming,striboh::base::Context pCtx) {
            "${myPrefix}\t\t\t auto myRetVal=${pMethodName}(
            theLambdaParameterList);
            "${myPrefix}\t\t\t );
            "${myPrefix}\t\t\t return striboh::base::Message(striboh::base::Value{myRetVal},getLog());
            "${myPrefix}\t\t },
            "${myPrefix}\t\t getLog()
            "${myPrefix}\t }
            """.format(myPrefix=myPrefix,pMethodName=pMethodName,myRetVal=myRetVal))
       self.theMethodNo += 1;

    def stribohIdlServantBeginParameter(self, pParameterName,pType):
       myCppType=striboh_type_to_cpp(pType)
       if self.__the_run_no__==1 :
           if theParNo>0 :
               self.addCode(self.theFilename, ", ")
           self.addCode(self.theFilename, "const ${myCppType} & ${pParameterName}"
                        .format(myCppType=myCppType,pParameterName=pParameterName))
       if self.__the_run_no__==2 :
           myPrefix = concat_prefix(theModuleDepth+1)
           myParameterTypeName = stribohTypeToTypeName(pType)
           if self.theParNo>0 :
               self.theLambdaParameterList += "${myPrefix}\t\t\t ,\n".format(myPrefix=myPrefix)
           self.addCode(self.theFilename, "${myPrefix}\t\t\t\t\t ,\n".format(myPrefix=myPrefix))
           self.theLambdaParameterList += "${myPrefix}\t\t\t pIncoming.getParameters()[${theParNo}].getValue().get<${myCppType}>()\n"\
               .format(myPrefix=myPrefix,theParNo=theParNo,myCppType=myCppType)
           self.addCode(self.theFilename, "${myPrefix}\t\t\t\t\t striboh::base::ParameterDescription{striboh::base::EDirection::K_IN, ${myParameterTypeName}, \"${pParameterName}\"}\n"
                        .format(myPrefix=myPrefix,myParameterTypeName=myParameterTypeName,pParameterName=pParameterName))
       self.theParNo = self.theParNo+1

#################### client visitor

class ClientVisitor(stribohIdl.PyAstVisitor):
    def __init__(self) {
       theRunNo=0;
       stribohIdlSetRuns(2);// set tree visitor runs
    }

    def stribohIdlClientBeginRun(pRunNo) {
        ++theRunNo;
    }

    def stribohIdlClientBeginModule(pModuleName) {
       theModuleNames.push_back(pModuleName);
    }

    def stribohIdlClientEndModule(pModuleName) {
       theModuleNames.pop_back();
    }

    global theMethodMessageCode = [];
    global theMethodCounter = 0;

    def generateModulePath(pModuleNames) {
        var myModulePath = "";
        for( var ii=0; ii<theModuleNames.size(); ++ii ) {
            if( ii == 0 ) {
                myModulePath += theModuleNames[ii];
            } else {
                myModulePath += "/";
                myModulePath += theModuleNames[ii];
            }
        }
        if(!theModuleNames.empty()) {
            myModulePath += "/";
        }
        return myModulePath;
    }

    def stribohIdlClientBeginInterface(pInterfaceName) {
        theIncludeGuard = "${pInterfaceName}_CLIENT_GUARD_HPP";
        var myPrefix=concat_prefix(theModuleDepth);
        theMethodCounter = 0;
        if(theRunNo==1) {
            theMethodMessageCode.clear();
            theFilename = "${pInterfaceName}Clt.hpp"
        }
       if(theRunNo==2) {
            addCode(theFilename,"#ifndef ${theIncludeGuard}\n");
            addCode(theFilename,"#define ${theIncludeGuard}\n");
            addCode(theFilename,"#include <string>\n");
            addCode(theFilename,"#include <vector>\n");
            addCode(theFilename,"#include <striboh/stribohBaseEMessageType.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseParameterList.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseMethod.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseMessage.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseInterface.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseProxyBase.hpp>\n");
            addCode(theFilename,"#include <striboh/stribohBaseBroker.hpp>\n");
            addCode(theFilename,"\n");
            generateNamespace(pInterfaceName);
            var myModulePath = generateModulePath(theModuleNames);
            addCode(theFilename,"${myPrefix}\t class ${pInterfaceName}Proxy : public striboh::base::ProxyBase {\n");// starting class ${pInterfaceName}Proxy\n");
            addCode(theFilename,"${myPrefix}\t public:\n");
            addCode(theFilename,"${myPrefix}\t\t ${pInterfaceName}Proxy(  std::string_view pHost, short pPort, striboh::base::LogIface& pLogIface )\n");
            addCode(theFilename,"${myPrefix}\t\t\t : striboh::base::ProxyBase(pHost, pPort, \"/${myModulePath}${pInterfaceName}\", pLogIface ) {}\n");
       }
       ++theModuleDepth;
    }

    def stribohIdlClientEndInterface(pInterfaceName) {
       var myPrefix=concat_prefix(theModuleDepth);
       if(theRunNo==2) {
            addCode(theFilename,"${myPrefix} };// end class ${pInterfaceName}\n");
            generateNamespaceClosing();
            addCode(theFilename,"#endif // ${theIncludeGuard}\n");
       }
       --theModuleDepth;
    }

    def stribohIdlClientBeginMethod(pMethodName,pReturnType) {
       var myMethodType = striboh_type_to_cpp(pReturnType);
       var myPrefix=concat_prefix(theModuleDepth);
       if(theRunNo==1) {
           theParNo = 0;
           theMethodMessageCode.push_back("${myPrefix} striboh::base::Message ${pMethodName}Msg(\"${pMethodName}\", {\n");
       }
       if(theRunNo==2) {
           theParNo = 0;
           addCode(theFilename, "${myPrefix}\t striboh::base::RetValProxy<${myMethodType}> ${pMethodName}(");
       }
    }

    def stribohIdlClientEndMethod(pMethodName,pReturnType) {
       var myPrefix=concat_prefix(theModuleDepth);
       if(theRunNo==1) {
           theMethodMessageCode[theMethodCounter] += "\n${myPrefix}\t\t } , getLog() ); // end method message"
       }
       if(theRunNo==2) {
           var myCppType=stribohTypeToCpp(pReturnType);
           addCode(theFilename, "){\n");
           addCode(theFilename, "${myPrefix}\t ${theMethodMessageCode[theMethodCounter]}\n");
           addCode(theFilename, "${myPrefix}\t\t return invoke(std::forward<striboh::base::Message>(${pMethodName}Msg), ${myCppType}{} ); // send request\n");
           addCode(theFilename, "${myPrefix}\t } // end method\n");
       }
       ++theMethodCounter;
    }

    def stribohIdlClientBeginParameter(pParameterName, pParameterType):
       var myParameterType = striboh_type_to_cpp(pParameterType);
       var myPrefix=concat_prefix(theModuleDepth);
       if(theRunNo==1) {
           if(theParNo==0) {
              theMethodMessageCode[theMethodCounter] += "${myPrefix}\t\t\t{ \"${pParameterName}\", ${pParameterName} }";
           } else {
              theMethodMessageCode[theMethodCounter] += ",\n${myPrefix}\t\t\t{ \"${pParameterName}\", ${pParameterName} }";
           }
           ++theParNo;
       }
       if(theRunNo==2) {
           if(theParNo>0) {
               addCode(theFilename, ", ");
           }
           addCode(theFilename, "${myParameterType} ${pParameterName}");
           self.theParNo +=1 ;

