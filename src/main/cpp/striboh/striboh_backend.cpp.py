import sys
sys.path.append('../lib','../../../cmake-build-debug/lib')
import stribohIdl

theRunNo=0;

def stribohIdlServantInit():
    stribohIdl.stribohIdlSetRuns(2);# set tree visitor runs

theIncludeGuard = "K_ECHO_SERVANT_GUARD_HPP";
theHeaderCode = "";

def stribohIdlServantBeginRun(pRun):
   ++theRunNo;
   if theRunNo==1 :
      theHeaderCode += "#ifndef ${theIncludeGuard}\n"
      theHeaderCode += "#define ${theIncludeGuard}\n"
      theHeaderCode += "#include <string>\n"
      theHeaderCode += "#include <vector>\n"
      theHeaderCode += "#include <striboh/stribohBaseEMessageType.hpp>\n"
      theHeaderCode += "#include <striboh/stribohBaseParameterList.hpp>\n"
      theHeaderCode += "#include <striboh/stribohBaseMethod.hpp>\n"
      theHeaderCode += "#include <striboh/stribohBaseMessage.hpp>\n"
      theHeaderCode += "#include <striboh/stribohBaseInterface.hpp>\n"
      theHeaderCode += "#include <striboh/stribohBaseServantBase.hpp>\n"
      theHeaderCode += "\n"


def concatPrefix(pDepth):
   myPrefix=""
   for ii=0 in range(pDepth):
      myPrefix=myPrefix+"\t"
   return myPrefix


def concatStringList(pList):
   myRetVal=""
   for ii in range(pList.size()):
      if ii > 0 :
          myRetVal=myRetVal+","
      myRetVal=myRetVal+"\""+pList[ii]+"\""
   return myRetVal


theModuleDepth = 0
theModuleNames = []
theModuleCodeBegin = ""

def generateNamespace(pInterfaceName):
    if !theModuleNames.empty() :
        addCode(theFilename, "namespace ")
    for ii in range(theModuleNames.size()) :
         if ii>0 :
             addCode(theFilename, "::");
         myNamespace=theModuleNames[ii];
         addCode(theFilename, "${myNamespace}");
    if !theModuleNames.empty() :
         addCode(theFilename, " {\n")
}

def generateNamespaceClosing() {
    if !theModuleNames.empty() :
        addCode(theFilename, "} // end namespace \n")
}


def stribohIdlServantBeginModule(pModuleName) {
   var myPrefix=concatPrefix(theModuleDepth);
   theModuleNames.push_back(pModuleName);
   ++theModuleDepth;
}

def stribohIdlServantEndModule(pModuleName) {
   --theModuleDepth;
   theModuleNames.pop_back();
}

global theMethodNo;
global theFilename="unknown";

def stribohIdlServantBeginInterface(pInterfaceName) {
   theMethodNo = 0;
   var myPrefix=concatPrefix(theModuleDepth);
   if(theRunNo==1) {
       theFilename = "${pInterfaceName}.hpp";
       addCode(theFilename, theHeaderCode);
       generateNamespace(pInterfaceName);
       addCode(theFilename, "${myPrefix} class ${pInterfaceName} : public striboh::base::ServantBase {\n");
       addCode(theFilename, "${myPrefix} public:\n");
   }
   if(theRunNo==2) {
       var myModuleList = concatStringList(theModuleNames);
       addCode(theFilename, "\n");
       addCode(theFilename, "${myPrefix}\t virtual const striboh::base::Interface& getInterface() const override { return mInterface; }\n\n");
       addCode(theFilename, "${myPrefix} private:\n");
       addCode(theFilename, "${myPrefix}\t striboh::base::Interface mInterface{\n");
       addCode(theFilename, "${myPrefix}\t\t *this,\n");
       print("Module list:${myModuleList}");
       addCode(theFilename, "${myPrefix}\t\t {${myModuleList}},\n");
       addCode(theFilename, "${myPrefix}\t\t striboh::base::InterfaceName{\"${pInterfaceName}\"},\n");
       addCode(theFilename, "${myPrefix}\t\t {\n");
   }
   ++theModuleDepth;
}

def stribohIdlServantEndInterface(pInterfaceName) {
   --theModuleDepth;
   var myPrefix=concatPrefix(theModuleDepth);
   if(theRunNo==2) {
       addCode(theFilename, "${myPrefix}\t\t }\n");
       addCode(theFilename, "${myPrefix}\t };\n");
       addCode(theFilename, "\n${myPrefix}};\n");
       addCode(theFilename, "\n} // end namespace\n");
       addCode(theFilename, "#endif // ${theIncludeGuard}");

   }
}

def stribohTypeToCpp(pStribohType) {
    if(pStribohType == "STRING") {
        return "std::string";
    }
    if(pStribohType == "INT") {
        return "int64_t";
    }
    throw (runtime_error("Unknown striboh type ${pStribohType}"));
}

def stribohTypeToTypeName(pStribohType) {
    if(pStribohType == "STRING") {
        return "striboh::base::ETypes::K_STRING";
    }
    if(pStribohType == "INT") {
        return "striboh::base::ETypes::K_INT";
    }
    throw (runtime_error("Unknown striboh type ${pStribohType}"));
}

global theParNo = -1;
global theLambdaParameterList;

def stribohIdlServantBeginMethod(pMethodName,pReturnType) {
   theParNo = 0;
   theLambdaParameterList = "";
   if(theRunNo==1) {
       var myPrefix=concatPrefix(theModuleDepth);
       var myCppType=stribohTypeToCpp(pReturnType);
       addCode(theFilename, "\n${myPrefix} virtual ${myCppType} ${pMethodName}(");
   }
   if(theRunNo==2) {
       var myPrefix=concatPrefix(theModuleDepth+1);
       if(theMethodNo>0) {
           addCode(theFilename, "${myPrefix}\t ,\n");
       }
       addCode(theFilename, "${myPrefix}\t striboh::base::Method{\"${pMethodName}\",\n");
       addCode(theFilename, "${myPrefix}\t\t striboh::base::ParameterDescriptionList{\n");
       addCode(theFilename, "${myPrefix}\t\t\t {\n");
   }
}

def stribohIdlServantEndMethod(pMethodName,pMethodType) {
   if(theRunNo==1) {
      addCode(theFilename, " ) = 0;\n");
   }
   if(theRunNo==2) {
      var myPrefix=concatPrefix(theModuleDepth+1);
      addCode(theFilename, "${myPrefix}\t\t\t }\n");
      addCode(theFilename, "${myPrefix}\t\t },\n");
      addCode(theFilename, "${myPrefix}\t\t [this](const striboh::base::Message &pIncoming,striboh::base::Context pCtx) {\n");
      addCode(theFilename, "${myPrefix}\t\t\t auto myRetVal=${pMethodName}(\n");
      addCode(theFilename, theLambdaParameterList);
      addCode(theFilename, "${myPrefix}\t\t\t );\n");
      addCode(theFilename, "${myPrefix}\t\t\t return striboh::base::Message(striboh::base::Value{myRetVal},getLog());\n");
      addCode(theFilename, "${myPrefix}\t\t },\n");
      addCode(theFilename, "${myPrefix}\t\t getLog()\n");
      addCode(theFilename, "${myPrefix}\t }\n");
   }
   theMethodNo += 1;
}

def stribohIdlServantBeginParameter(pParameterName,pType) {
   var myCppType=stribohTypeToCpp(pType);
   if(theRunNo==1) {
       if(theParNo>0) {
          addCode(theFilename, ", ");
       }
       addCode(theFilename, "const ${myCppType} & ${pParameterName}");
   }
   if(theRunNo==2) {
       var myPrefix = concatPrefix(theModuleDepth+1);
       var myParameterTypeName = stribohTypeToTypeName(pType);
       if(theParNo>0) {
          theLambdaParameterList += "${myPrefix}\t\t\t ,\n";
          addCode(theFilename, "${myPrefix}\t\t\t\t\t ,\n");
       }
      theLambdaParameterList += "${myPrefix}\t\t\t pIncoming.getParameters()[${theParNo}].getValue().get<${myCppType}>()\n";
      addCode(theFilename, "${myPrefix}\t\t\t\t\t striboh::base::ParameterDescription{striboh::base::EDirection::K_IN, ${myParameterTypeName}, \"${pParameterName}\"}\n");
   }
   theParNo = theParNo+1;
}

def stribohIdlClientInit() {
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
    var myPrefix=concatPrefix(theModuleDepth);
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
   var myPrefix=concatPrefix(theModuleDepth);
   if(theRunNo==2) {
        addCode(theFilename,"${myPrefix} };// end class ${pInterfaceName}\n");
        generateNamespaceClosing();
        addCode(theFilename,"#endif // ${theIncludeGuard}\n");
   }
   --theModuleDepth;
}

def stribohIdlClientBeginMethod(pMethodName,pReturnType) {
   var myMethodType = stribohTypeToCpp(pReturnType);
   var myPrefix=concatPrefix(theModuleDepth);
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
   var myPrefix=concatPrefix(theModuleDepth);
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

def stribohIdlClientBeginParameter(pParameterName, pParameterType) {
   var myParameterType = stribohTypeToCpp(pParameterType);
   var myPrefix=concatPrefix(theModuleDepth);
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
       ++theParNo;
   }
}
