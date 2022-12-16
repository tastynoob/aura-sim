#pragma once

#include "base/dyninst.hh"
#include "base/port.hh"
#include "base/timing.hh"
#include "cpu/comm.hh"


namespace aura
{
class O3CPU;

class Decode
{
    O3CPU* cpu;
    TimingBuffer<DecodeStruct>* decodeTimingBuffer;

  public:
    Decode(O3CPU* cpu, TimingBuffer<DecodeStruct>* buffer);
    void Tick();
    void Advance();
    void Dump();
};
}