#pragma once
#include "base/dyninst.hh"
#include "base/timing.hh"
#include "base/types.hh"
#include "cpu/comm.hh"
#include "cpu/frontend/fetch.hh"


namespace aura
{
class O3CPU : public Device
{
  public:
    // fetch access ports
    std::vector<MasterPort*> iPort;
    // load-store access ports
    std::vector<MasterPort*> dPort;

  private:
    // List of all the instructions in flight.
    std::list<DynInstPtr> flightInstList;
    TimingBuffer<FetchStruct> fetchTimingBuffer;
    TimingBuffer<DecodeStruct> decodeTimingBuffer;
    Fetch* fetch;

  public:
    O3CPU();
    void Tick(u64 tick);
    void Advance();

    std::vector<MasterPort*>& GetFetchPorts();
    std::vector<MasterPort*> GetDataPorts();
    // to memory system
};
}  // namespace aura