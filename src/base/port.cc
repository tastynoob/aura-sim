#include "port.hh"

namespace aura
{
MasterPort::MasterPort(u32 portBusWidth) : portBusWidth(portBusWidth)
{
    for (int i = 0; i < toSlaveData.BufferSize(); i++) {
        toSlaveData.GetBuffer()[i].wrdBuffer = new u8[portBusWidth];
    }
}

void
MasterPort::Clear()
{
    // clear all request functional
    for (int i = 0; i < toSlaveData.BufferSize(); i++) {
        toSlaveData.GetBuffer()[i].size = 0;
    }
}

ToSlaveStruct*
MasterPort::Req(u32 size)
{
    assert(size <= portBusWidth);
    toSlaveData.Curr().size = size;
    return &(toSlaveData.Curr());
}

std::pair<u8*, u32>
MasterPort::Input()
{
    return std::make_pair(toSlaveData.Last().wrdBuffer,
                          toSlaveData.Last().Size());
}
ToSlaveStruct*
MasterPort::Rereq(u32 size)
{
    Clear();
    assert(size <= portBusWidth);
    toSlaveData.Prev().size = size;
    return &(toSlaveData.Prev());
}

ToMasterStruct*
MasterPort::Rsp()
{
    assert(fromSlaveData != nullptr);
    return &(fromSlaveData->Last());
}


void
MasterPort::Advance()
{
    toSlaveData.Advance();
}

void
MasterPort::SetSlavePort(SlavePort* toSlave)
{
    toSlave->SetMasterPort(this);
}

ToMasterStruct*
SlavePort::Output()
{
    return &(toMasterData.Curr());
}

ToSlaveStruct*
SlavePort::Input()
{
    assert(fromMasterData != nullptr);
    return &(fromMasterData->Last());
}

void
SlavePort::Advance()
{
    toMasterData.Advance();
}

void
SlavePort::SetMasterPort(MasterPort* master)
{
    assert(fromMasterData == nullptr);
    fromMasterData = &(master->toSlaveData);
    master->fromSlaveData = &toMasterData;
}
}