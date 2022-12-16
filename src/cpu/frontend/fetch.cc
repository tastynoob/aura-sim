#include "cpu/frontend/fetch.hh"
#include "cpu/o3cpu.hh"


namespace aura
{
Fetch::Fetch(O3CPU* cpu, TimingBuffer<FetchStruct>* buffer)
{
    this->cpu = cpu;
    this->fetchTimingBuffer = buffer;
    pc = 0x0;
}

void
Fetch::Tick()
{
    // todo
    bool continueFetch = true;
    bool branch = false;
    auto fetchPort = cpu->GetFetchPorts()[0];
    assert(fetchPort != nullptr);
    if (curStatus == Status::RST) {
        curStatus = Status::Request;
        return;
    } else if (curStatus == Status::Request) {
        curStatus = Status::Fetching;
        SendFetchReq(pc);
        pc += L1ICACHELINESIZE;
        return;
    } else if (curStatus == Status::Fetching) {
        // when branch,we need to clear past requests
        if (branch) {
            fetchPort->Clear();
            curStatus = Status::Request;
            return;
        }
        if (fetchPort->Rsp()->error) {
            throw "fetch error !";
        }
        // request success
        if (fetchPort->Rsp()->success) {
            auto [byteStream, byteSize] = fetchPort->Input();
            write(fileno(stdout), (void*)byteStream, byteSize);
            for (int i = 0; i < byteSize / 4; i++) {
                auto [inst0, inst1] =
                    DynInst::MakeInst(*(((u32*)byteStream) + i));
                if (inst0) {
                    fetchInst.push(inst0);
                    inst0->SetIterator(cpu->AddFlightInst(inst0));
                    if (inst1) {
                        fetchInst.push(inst1);
                        inst1->SetIterator(cpu->AddFlightInst(inst1));
                    }
                }
            }
        }

        // insert leftoverBuffer into fetchQue
        for (int i = 0; i < FETCHWIDTH; i++) {
            if ((!fetchInst.empty()) &&
                cpu->fetchQue->Push(fetchInst.front())) {
                fetchInst.pop();
            } else {
                break;
            }
        }
        // leftoverBuffer save up to L1ICACHELINESIZE / 16 instructions
        // and to prevent overflow
        // once number of saved instructions biger than
        // L1ICACHELINESIZE / 16 - FETCHWIDTH
        // then stop fetch
        assert(fetchInst.size() <= L1ICACHELINESIZE / 2);
        // std::cout << leftoverBuffer.size() << std::endl;
        if (fetchInst.size() > L1ICACHELINESIZE / 2 - FETCHWIDTH ||
            cpu->fetchQue->Full()) {
            // std::cout << "stop fetch!" << std::endl;
            fetchPort->Clear();
            // pc go back
            pc -= L1ICACHELINESIZE;
            continueFetch = false;
        }
        if (continueFetch) {
            // std::cout << "send req!" << std::endl;
            SendFetchReq(pc);
            pc += L1ICACHELINESIZE;
        }
    }
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
    auto request = cpu->GetFetchPorts()[0]->Req(L1DCACHELINESIZE);
    request->address = pc;
    request->write = false;
    return true;
}
}