#include "cpu/o3cpu.hh"
#include "mem/tcm.hh"
#include <bits/stdc++.h>

int
main(int, char**)
{
    aura::O3CPU* cpu = new aura::O3CPU();
    aura::TCM* tcm =
        new aura::TCM("/media/lurker/CACHE/O3CPU/aura-sim/CMakeLists.txt");
    // link
    for(auto it : cpu->GetFetchPorts()){
        tcm->AddMasterPort(it);
    }
    for (auto it : cpu->GetDataPorts()) {
        tcm->AddMasterPort(it);
    }

    u64 global_tick = 0;
    do {
        cpu->Tick(global_tick);
        tcm->Tick(global_tick);
        cpu->Advance();
        tcm->Advance();
    } while (++global_tick < 10);
}
