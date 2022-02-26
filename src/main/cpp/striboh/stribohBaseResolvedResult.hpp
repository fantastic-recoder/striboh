#pragma once

#include <set>
#include "striboh/stribohBase.hpp"
#include "striboh/stribohBaseAddress.hpp"
#include "striboh/stribohBaseInstanceId.hpp"

namespace striboh::base {
    enum class EResolveResult {
        NOT_FOUND,
        OK
    };

    using ModuleNames = std::set<ModuleName>;
    using InterfaceNames = std::set<InterfaceName>;

    struct ResolvedResult {
        EResolveResult m_Result = EResolveResult::NOT_FOUND;
        ModuleNames m_Modules;
        Path m_Path;
        InterfaceNames m_Interfaces;
        const Address &m_Address;

        ResolvedResult(const Address &p_Address) : m_Address(p_Address) {};
    };

    using ResolvedService = std::pair<bool, InstanceId>;

}