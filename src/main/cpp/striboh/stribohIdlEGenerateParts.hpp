
#ifndef STRIBOH_IDL_EGENERATEPARTS_HPP
#define STRIBOH_IDL_EGENERATEPARTS_HPP

namespace striboh::idl {

    /**
     * What parts should be generated.
     * EGeneratedParts.EClient generate only client part.
     * EGeneratedParts.EServant generate only servant part
     * EGeneratedParts.EBoth generate both parts.
     */
    enum class EGenerateParts : uint8_t {
        EClient /*---001-*/ = 1,
        EServant /*--010-*/ = 2,
        EBoth /*-----011-*/ = 3,
        ENone /*-----000-*/ = 0
    };

}
#endif //STRIBOH_IDL_EGENERATEPARTS_HPP
