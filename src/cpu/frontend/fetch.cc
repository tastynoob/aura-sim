#include "cpu/frontend/fetch.hh"
#include "cpu/o3cpu.hh"


namespace aura
{
Fetch::Fetch(O3CPU* cpu, TimingBuffer<FetchStruct>* buffer)
{
    this->cpu = cpu;
    this->fetchTimingBuffer = buffer;

}

void
Fetch::Tick()
{
    // todo
    bool continueFetch = true;
    bool branch = false;
    auto fetchPort = cpu->GetFetchPorts()[0];
    bool isGetBytes = false;
    auto [byteStream, byteSize] = fetchPort->Input();
    assert(fetchPort != nullptr);

    //stage2: get bytes and process
    if (fetchPort->Rsp()->success){
        u32 valid_offset = lastpc & (L1ICACHELINESIZE - 1);
        u32 valid_size = L1ICACHELINESIZE - valid_offset;

    }

    //stage1: wait for bytes 


    //stage0:




}

void
Fetch::Advance()
{
}

void
Fetch::Dump()
{
}

bool
Fetch::SendFetchReq(Addr pc)
{
    auto request = cpu->GetFetchPorts()[0]->Req(L1ICACHELINESIZE);
    request->address = pc & ~(L1ICACHELINESIZE - 1);
    request->write = false;
    return true;
}
}