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
    switch (curStatus) {
        case Status::RST:
            curStatus = Status::Request;
            return;
        case Status::Request:
            curStatus = Status::Fetching;
            return;
        case Status::Fetching:
            break;
        default:
            break;
    }

}


}