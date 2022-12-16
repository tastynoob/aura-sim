#include "timing.hh"

namespace aura
{

void
Device::Tick(u64 tick)
{
    throw "this device has no Tick function!";
}

void
Device::Advance()
{
    throw "this device has no Advance function!";
}

void
Device::AddMasterPort(MasterPort* masterPort)
{
    throw "this device has no Master port process function!";
}


void
Device::AddSlavePort(SlavePort* slavePort)
{
    throw "this device has no Slave port process function!";
}
}