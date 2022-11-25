#pragma once

#include "base/types.hh"

namespace aura
{
// base timing module : input->register->logic_calculate->output
template<typename T, int cycle = 2>
class TimingBuffer
{
    u64 total_tick = 0;
    T buffer[cycle];
    u8 prev_one = 1;
    u8 last_one = cycle - 1;

  public:
    TimingBuffer() : last_one(cycle - 1) {}
    void Advance()
    {
        total_tick++;
        if (++last_one >= cycle) {
            last_one = 0;
        }
        if (++prev_one >= cycle) {
            prev_one = 0;
        }
    }
    T& Curr() { return buffer[total_tick % cycle]; }
    // the prev cycle value
    T& Prev() { return buffer[prev_one]; }
    // the last cycle value
    T& Last() { return buffer[last_one]; }
    T& Access(u64 tick) { return buffer[tick % cycle]; }
    T& operator[](u64 tick) { return Access(tick); }
    u32 BufferSize() const { return cycle; }
    T* GetBuffer() { return buffer; }
};

class MasterPort;
class SlavePort;
class Device
{
  public:
    virtual void Tick(u64 tick);
    virtual void Advance();
    virtual void AddMasterPort(MasterPort* masterPort);
    virtual void AddSlavePort(SlavePort* slavePort);
};

}  // namespace aura
