#include "base.hh"

namespace aura
{
void
BaseMem::Advance()
{
    for (auto& it : fromMasterPorts) {
        it->Advance();
    }
}
void
BaseMem::AddMasterPort(MasterPort* masterPort)
{
    SlavePort* slave = new SlavePort();
    slave->SetMasterPort(masterPort);
    fromMasterPorts.push_back(slave);
}
}