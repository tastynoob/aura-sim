#include "dyninst.hh"

namespace aura
{
DynInst::DynInst() {}

std::pair<DynInstPtr, DynInstPtr>
DynInst::MakeInst(u32 instbitcode)
{
    // todo:just support uncompressed instruction
    // todo:decode the instbitcode
    return std::make_pair(new DynInst(), new DynInst());
}
}