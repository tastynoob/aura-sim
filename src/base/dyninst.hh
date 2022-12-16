#pragma once
#include "base/opclass.hh"
#include "base/types.hh"

namespace aura
{
class DynInst;
using DynInstPtr = DynInst*;
/// @brief it will be create when an inst insert into rob
class DynInst
{
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
    std::list<DynInstPtr>::iterator it;

  public:
    InstStatus status;
    u64 seq;
    RegVal result;
    RegVal imm;
    Addr pc;
    u8 numDstRegs;
    u8 numSrcRegs;
    RegId dst;
    RegId src1;
    RegId src2;
    DynInst();
    void SetIterator(std::list<DynInstPtr>::iterator it) { this->it = it; }
    //it will return one 32bit inst or two compressed insts
    static std::pair<DynInstPtr,DynInstPtr> MakeInst(u32 instbitcode);
    std::list<DynInstPtr>::iterator GetIterator() { return this->it; }
};

}  // namespace aura
