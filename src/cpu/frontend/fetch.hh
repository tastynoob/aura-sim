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
    enum class Status { RST, Request, Fetching, Blocking };
    Status curStatus = Status::RST;
    // fetchU insert up to FETCHWIDTH instructions into fetchbuffer
    // so we need push extra instructions into leftOverBuffer
    // it's max size is L1ICacheLineSize/16 * 2
    std::queue<DynInstPtr> fetchInst;
    Addr pc;

  public:
    Fetch(O3CPU* cpu, TimingBuffer<FetchStruct>* buffer);
    void Tick();
    void Advance();
    void Dump();


  private:
    bool SendFetchReq(Addr pc);
};
}  // namespace aura
