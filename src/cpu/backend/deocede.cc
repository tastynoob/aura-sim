#include "cpu/backend/deocede.hh"
#include "cpu/o3cpu.hh"

namespace aura
{
Decode::Decode(O3CPU* cpu, TimingBuffer<DecodeStruct>* buffer)
{
    this->cpu = cpu;
    this->decodeTimingBuffer = buffer;
}

void
Decode::Tick()
{
    for (int i = 0; i < DECODEWIDTH; ++i) {
        if (!(cpu->fetchQue->Empty())) {
            DynInstPtr it = cpu->fetchQue->Pop();
            decodeTimingBuffer->Curr().decodeSize = i + 1;
            decodeTimingBuffer->Curr().insts[i] = it;
        } else {
            break;
        }
    }
}

void
Decode::Advance()
{
}

void
Decode::Dump()
{
}
}