#include "port.hh"

namespace aura
{
ToSlaveStruct*
MasterPort::Output()
{
    return &(toSlavePort.Curr());
}

ToMasterStruct* MasterPort::Input()
{
    assert(fromSlavePort != nullptr);
    return &(fromSlavePort->Last());
}

void
MasterPort::Advance()
{
    toSlavePort.Advance();
}

void
MasterPort::SetSlavePort(SlavePort* toSlave)
{
    toSlave->SetMasterPort(this);
}

ToMasterStruct*
SlavePort::Output()
{
    return &(toMasterPort.Curr());
}

ToSlaveStruct* SlavePort::Input()
{
    assert(fromMasterPort != nullptr);
    return &(fromMasterPort->Last());
}

void
SlavePort::Advance()
{
    toMasterPort.Advance();
}

void
SlavePort::SetMasterPort(MasterPort* master)
{
    assert(fromMasterPort == nullptr);
    fromMasterPort = &(master->toSlavePort);
    master->fromSlavePort = &toMasterPort;
}
}