#include "cpu/o3cpu.hh"
#include "mem/tcm.hh"
#include <bits/stdc++.h>

int
main(int, char**)
{
    aura::MasterPort masterPort(8);
    aura::TCM* tcm =
        new aura::TCM("/media/lurker/CACHE/O3CPU/aura-sim/CMakeLists.txt");
    tcm->AddMasterPort(&masterPort);
    u64 global_tick = -1;
    while (++global_tick < 15) {
        masterPort.Output()->size = rand() % 2 ? 8 : 0;
        masterPort.Output()->address = global_tick * 8;
        masterPort.Output()->write = false;
        tcm->Tick(global_tick);
        tcm->Advance();
        masterPort.Advance();
        std::cout << "[ Tick ] : " << global_tick << std::endl;
        if (masterPort.Input()->success) {
            std::cout << masterPort.Output()->wrdBuffer << std::endl;
        }
    }
}
