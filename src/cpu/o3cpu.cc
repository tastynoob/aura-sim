#include "cpu/o3cpu.hh"


namespace aura
{
O3CPU::O3CPU()
{
    for (int i = 0; i < DPORTS; i++) {
        iPort.push_back(new MasterPort(L1ICACHELINESIZE));
    }
    for (int i = 0; i < DPORTS; i++) {
        dPort.push_back(new MasterPort(L1DCACHELINESIZE));
    }
}
}