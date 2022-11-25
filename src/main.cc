#include "cpu/o3cpu.hh"
#include "mem/tcm.hh"
#include <bits/stdc++.h>

int
main(int, char**)
{
    aura::MasterPort masterPort;
    aura::TCM* tcm =
        new aura::TCM("/media/lurker/CACHE/O3CPU/aura-sim/CMakeLists.txt");
    tcm->AddMasterPort(&masterPort);
    u64 global_tick = -1;
    masterPort.Output()->wrdBuffer = new u8[100]{0};
    while (++global_tick < 10000000) {
        masterPort.Output()->size = 8;
        masterPort.Output()->address = 0;
        masterPort.Output()->write = false;
        tcm->Tick(global_tick);
        tcm->Advance();
        masterPort.Advance();
        std::cout << "Tick:" << global_tick << std::endl;
        if (masterPort.Input()->success) {
            std::cout << masterPort.Output()->wrdBuffer << std::endl;
        }
    }
}
