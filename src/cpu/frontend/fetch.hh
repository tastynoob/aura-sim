#pragma once

#include "base/dyninst.hh"
#include "base/port.hh"
#include "base/timing.hh"
#include "cpu/comm.hh"

namespace aura
{
class O3CPU;

class Fetch
{
    O3CPU* cpu;
    TimingBuffer<FetchStruct>* fetchTimingBuffer;

    struct FStage0
    {
        Addr pc;
    } s0;

    // when fetcher get bytestream
    struct FStage1
    {
        Addr pc;
        u32 leftover_size;
        u8 leftover_buffer[L1ICACHELINESIZE];
    } s1;

    struct FStage2
    {

    }s2;
    

    Addr lastpc;

  public:
    Fetch(O3CPU* cpu, TimingBuffer<FetchStruct>* buffer);
    void Tick();
    void Advance();
    void Dump();


  private:
    bool SendFetchReq(Addr pc);
};
}  // namespace aura
