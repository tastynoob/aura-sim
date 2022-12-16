#include "cpu/o3cpu.hh"
#include "cpu/backend/deocede.hh"
#include "cpu/frontend/fetch.hh"


namespace aura
{
O3CPU::O3CPU()
{
    //ibus and dbus
    for (int i = 0; i < DPORTS; i++) {
        iPorts.push_back(new MasterPort(L1ICACHELINESIZE));
    }
    for (int i = 0; i < DPORTS; i++) {
        dPorts.push_back(new MasterPort(L1DCACHELINESIZE));
    }
    //fetch stage
    fetch = new Fetch(this, &fetchTimingBuffer);
    fetchQue = new FetchQue();

    decode = new Decode(this, &decodeTimingBuffer);
}

void
O3CPU::Tick(u64 tick)
{
    // tick
    fetch->Tick();
    decode->Tick();
}

void
O3CPU::Advance()
{
    // fetch
    fetch->Advance();
    fetchTimingBuffer.Advance();
    fetchQue->Advance();

    decode->Advance();

    for (auto it : iPorts) {
        it->Advance();
    }
    for (auto it : dPorts) {
        it->Advance();
    }
}

std::list<DynInstPtr>::iterator
O3CPU::AddFlightInst(DynInstPtr new_ins)
{
    flightInstList.push_back(new_ins);
    auto it = flightInstList.end();
    new_ins->SetIterator(it);
    return it;
}

std::vector<MasterPort*>&
O3CPU::GetFetchPorts()
{
    return iPorts;
}
std::vector<MasterPort*>&
O3CPU::GetDataPorts()
{
    return dPorts;
}
}