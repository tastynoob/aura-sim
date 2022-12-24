#pragma once
#include "base/dyninst.hh"
#include "base/timing.hh"
#include "base/types.hh"
#include "cpu/comm.hh"


namespace aura
{
class Fetch;
class Decode;
class O3CPU : public Device
{
    using FetchQue = Fifo<DynInstPtr, FETCHBUFFERSIZE>;

    // fetch access ports
    std::vector<MasterPort*> iPorts;
    // load-store access ports
    std::vector<MasterPort*> dPorts;

  public:
    TimingBuffer<FetchStruct> fetchTimingBuffer;
    TimingBuffer<DecodeStruct> decodeTimingBuffer;

    FetchQue* fetchQue;

  private:
    // List of all the instructions in flight.
    std::list<DynInstPtr> flightInstList;
    Fetch* fetch;
    Decode* decode;


  public:

    O3CPU();
    void Tick(u64 tick);
    void Advance();
    // insert into flightInstList when fetch insts
    std::list<DynInstPtr>::iterator AddFlightInst(DynInstPtr new_ins);


    std::vector<MasterPort*>& GetFetchPorts();
    std::vector<MasterPort*>& GetDataPorts();
    // to memory system
};
}  // namespace aura