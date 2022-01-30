//
// Created by coder.peter.grobarcik@gmail.com on 7/19/20.
//

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include "stribohIdlAstRootNode.hpp"
#include "stribohIdlAstImportNode.hpp"
#include "stribohIdlAstVisitor.hpp"
#include "stribohIdlAstModuleBodyNode.hpp"

namespace {
    static const std::string K_ROOT_VAL = "<root>";
}

namespace striboh {
    namespace idl {
        namespace ast {
            using std::vector;
            using std::string;
            using boost::fusion::at_c;

            std::ostream& operator<<(std::ostream& pOstream, const RootNode& pNode) {
                pNode.printAstNode(0, pOstream);
                return pOstream;
            }

            void RootNode::mergeSubtree(const RootNode& pSubtree) {
                getErrors().insert(getErrors().begin(),
                                   pSubtree.getErrors().begin(),
                                   pSubtree.getErrors().end());
                getImports().insert(getImports().begin(),
                                    pSubtree.getImports().begin(),
                                    pSubtree.getImports().end());
                getModules().insert(getModules().begin(),
                                    pSubtree.getModules().begin(),
                                    pSubtree.getModules().end());
            }

            std::string_view RootNode::getValueStr() const {
                return K_ROOT_VAL;
            }

            void RootNode::visit(striboh::idl::AstVisitor &pVisitor) {
                auto& myModules=getModules();
                visitModules(pVisitor, myModules);
            }

            void RootNode::visitModules(AstVisitor &pVisitor, const ModuleListNode &pModules) const {
                for( const auto& pModule: pModules ) {
                    const auto& myModuleName = pModule.getIdentifierStr();
                    pVisitor.beginModule(myModuleName);
                    auto& myInterfaces = pModule.getModuleBody().getInterfaces();
                    for( const auto& myInterface : myInterfaces ) {
                        const string& myInterfaceName = myInterface.getName();
                        pVisitor.beginInterface(myInterfaceName);
                        const auto& myMethods=myInterface.getMethods();
                        for( const auto& myMethod : myMethods ) {
                            pVisitor.beginMethod(myMethod[0]);
                            for( size_t myI = 1; myI < myMethod.size(); myI++) {
                                pVisitor.beginParameter(myMethod[myI]);
                            }
                            pVisitor.endMethod(myMethod[0]);
                        }
                        pVisitor.endInterface(myInterfaceName);
                    }
                    visitModules(pVisitor,pModule.getModuleBody().getModules());
                    pVisitor.endModule(myModuleName);
                };
            }

            RootNode& RootNode::operator += (const ModuleBodyNode& pModuleBodyNode) {
                copy(pModuleBodyNode.getModules().begin(),pModuleBodyNode.getModules().end(),
                     std::back_inserter(getModules()));
                //this->getModules().push_back(pModuleBodyNode);
                BOOST_LOG_TRIVIAL(trace) << "Add module to root ("<< this <<") new size=" << pModuleBodyNode.getModules().size() <<".";
                return *this;
            }

            RootNode &RootNode::operator+=(const vector<std::string> &) {
                return *this;
            }


        }
    } // end idl
} // end striboh

