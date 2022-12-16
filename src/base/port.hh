#pragma once
#include "base/timing.hh"


namespace aura
{
class ToSlaveStruct
{
    friend class MasterPort;

  private:
    u32 size = 0;

  public:
    Addr address;
    bool write;
    u8* wrdBuffer = nullptr;
    // this packet request size
    u32 Size() { return size; }
};
class ToMasterStruct
{
  public:
    // access except
    bool error = false;
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
    MasterTimingBuffer toSlaveData;
    // slave device call master advance
    SlaveTimingBuffer* fromSlaveData = nullptr;
    u32 portBusWidth;

  public:
    MasterPort(u32 portBusWidth);
    void Clear();
    // set request size
    // return request handle of current tick
    ToSlaveStruct* Req(u32 size);
    // return pair<dataBuffer,dataSize>
    std::pair<u8*, u32> Input();
    // clear the past requests
    // and reset prev request
    // mainly used to simulate the handshake fail and cancel the request
    ToSlaveStruct* Rereq(u32 size);
    // the respond of slave
    ToMasterStruct* Rsp();
    void Advance();
    void SetSlavePort(SlavePort* toSlave);
};
// the slave devide port to master
// SlavePort save the toMasterStruct data;
class SlavePort
{
    SlaveTimingBuffer toMasterData;
    MasterTimingBuffer* fromMasterData = nullptr;


  public:
    ToMasterStruct* Output();
    ToSlaveStruct* Input();
    void Advance();
    // slaver call this to set Master
    void SetMasterPort(MasterPort* master);
};
}  // namespace aura
