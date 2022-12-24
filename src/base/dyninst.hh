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
    u8 numDstRegs;
    u8 numSrcRegs;
    RegId dests[1];
    RegId srcs[3];
    PhyRegId dests[1];
    PhyRegId srcs[3];

  public:
    InstStatus status;
    u64 seq;
    RegVal result;
    RegVal imm;
    Addr pc;

    DynInst();
    u8 NumDstRegs() const;
    u8 NumSrcRegs() const;
    RegId GetSrcRegId(u8 n);
    RegId GetDstRegId(u8 n);
    void RenameDst(u8 n, PhyRegId regid);
    void RenameSrc(u8 n, PhyRegId regid);
    void SetIterator(std::list<DynInstPtr>::iterator it) { this->it = it; }
    //it will return one 32bit inst or two compressed insts
    static std::pair<DynInstPtr,DynInstPtr> MakeInst(u32 instbitcode);
    std::list<DynInstPtr>::iterator GetIterator() { return this->it; }
};

}  // namespace aura
