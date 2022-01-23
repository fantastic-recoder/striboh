
#ifndef STRIBOH_STRIBOHIDLPYMODULE_HPP
#define STRIBOH_STRIBOHIDLPYMODULE_HPP

#include <fmt/format.h>
#include "striboh/stribohIdlCompiler.hpp"
#include "striboh/stribohIdlAstVisitor.hpp"
#include "striboh/stribohIdlAstTypedIdentifierNode.hpp"
#include "striboh/stribohIdlParser.hpp"
#include "striboh/stribohBaseLogIface.hpp"

namespace striboh {
    namespace idl {
        const char *const version();

        int process(std::vector<std::string> pArg);

        void setBackendVisitors(AstVisitor &pClientBackend, AstVisitor &pServantBackend);

        class PyAstVisitor : public AstVisitor {
        public:
            using AstVisitor::AstVisitor;

            ~PyAstVisitor() override = default;

            void beginRun(int pRunNum) override;

            void beginModule(std::string_view pModuleName) override;

            void endModule(std::string_view pModuleName) override;

            void beginInterface(std::string_view pInterfaceName) override;

            void endInterface(std::string_view pInterfaceName) override;

            void beginMethod(const ast::TypedIdentifierNode &pMethod) override;

            void endMethod(const ast::TypedIdentifierNode &pMethod) override;

            void beginParameter(const ast::TypedIdentifierNode &pPar) override;
        };

        void initPythonTypes(pybind11::module_ p_pyModule);

    }
}

#endif //STRIBOH_STRIBOHIDLPYMODULE_HPP
