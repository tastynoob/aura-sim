#pragma once
#include "base/timing.hh"


namespace aura
{
struct ToSlaveStruct
{
    u8 size = 0;
    Addr address;
    bool write;
    u8* wrdBuffer;
};
struct ToMasterStruct
{
    bool except = false;
    bool success = false;
};
using MasterTimingBuffer = TimingBuffer<ToSlaveStruct>;
using SlaveTimingBuffer = TimingBuffer<ToMasterStruct>;
class SlavePort;
class MasterPort;
// the master devide port to slave
class MasterPort
{
    friend class SlavePort;
    // master device call toSlavePort advance
    MasterTimingBuffer toSlavePort;
    // slave device call master advance
    SlaveTimingBuffer* fromSlavePort = nullptr;

  public:
    MasterPort(u32 dataBufferSize);
    ToSlaveStruct* Output();
    ToMasterStruct* Input();
    void Advance();
    void SetSlavePort(SlavePort* toSlave);
};
// the slave devide port to master
class SlavePort
{
    SlaveTimingBuffer toMasterPort;
    MasterTimingBuffer* fromMasterPort = nullptr;


  public:
    ToMasterStruct* Output();
    ToSlaveStruct* Input();
    void Advance();
    // slaver call this to set Master
    void SetMasterPort(MasterPort* master);
};
}  // namespace aura
