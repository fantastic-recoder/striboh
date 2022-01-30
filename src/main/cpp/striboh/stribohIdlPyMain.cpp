#include <pybind11/embed.h> // everything needed for embedding

#include <striboh/stribohBaseLogBoostImpl.hpp>
#include <striboh/stribohIdlCompiler.hpp>
#include <striboh/stribohIdlPyModule.hpp>

namespace py = pybind11;

using striboh::idl::Compiler;
using striboh::idl::version;
using striboh::idl::process;
using striboh::idl::setBackendVisitors;
using striboh::idl::initPythonTypes;

PYBIND11_EMBEDDED_MODULE(stribohmodule, p_pyModule)
{
    p_pyModule.doc() = "Striboh Embedded Python module"; // optional module docstring
    p_pyModule.def("version", version, "Print module version.");
    p_pyModule.def("process", process, "Process the command the IDL sources specified on command line.");
    p_pyModule.def("setBackendVisitors",setBackendVisitors, "Set the visitors to be called upon backend code "
                                                            "generation.");
    initPythonTypes(p_pyModule);
}


int main( int argc, char** argv) {

    py::scoped_interpreter guard{}; // start the interpreter and keep it alive
    Compiler myCompiler(striboh::base::getGlobalLog());
    auto myRetVal=myCompiler.pyProcess(argc,argv);
    return myRetVal;
}
