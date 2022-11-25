#pragma once
#include "base/opclass.hh"
#include "base/types.hh"

namespace aura {
class DynInst;
using DynInstPtr = DynInst*;
/// @brief it will be create when an inst insert into rob
class DynInst {
    enum class InstStatus {
        None,
        Decoding,
        Renaming,
        Dispatching,
        Executing,
        Executed,
        Squashed,
        CanCommit,
    };

  public:
    InstStatus status;
    u64 seq;
    RegVal result;
    Addr pc;
    DynInst(u32 inst);
};

}  // namespace aura
