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
    Addr pc;

  public:
    Fetch(O3CPU* cpu, TimingBuffer<FetchStruct>* buffer);
    void Init();
    void Tick();
    void Dump();
    void Advance();
private:
    bool SendFetchReq();
};
}  // namespace aura
