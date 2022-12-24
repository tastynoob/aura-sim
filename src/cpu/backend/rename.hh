#pragma once

#include "base/dyninst.hh"
#include "base/port.hh"
#include "base/timing.hh"
#include "cpu/comm.hh"


namespace aura
{
class O3CPU;

class Rename
{
    O3CPU* cpu;
    TimingBuffer<RenameStruct>* renameTimingBuffer;
    Fifo<PhyRegId, 196> freeList;
    std::map<RegId, PhyRegId> maptable;

    std::deque<DynInstPtr> skidBuffer;

  public:
    Rename(O3CPU* cpu, TimingBuffer<RenameStruct>* buffer);
    void Tick();
    PhyRegId RenameDst(RegId archRegid);
    PhyRegId RenameSrc(RegId archRegid);
    void Advance();
    void Dump();
};
}