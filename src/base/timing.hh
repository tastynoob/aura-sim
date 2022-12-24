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
    const int bufferSize = cycle;

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


template<typename T, u32 MaxSize>
class Fifo
{
  private:
    // past and curr timingbuffer use the same fetchbuffer
    // being used to save memory and improve executing speed
    u32 size_curr, size_prev;
    std::queue<T> buffer;

  public:
    u32 Size() { return size_prev; }
    void Clear()
    {
        size_curr = 0;
        size_prev = 0;
    }
    // only for write
    bool Full()
    {
        assert(size_curr <= MaxSize);
        return size_curr == MaxSize;
    }
    // only for read
    bool Empty()
    {
        assert(size_prev <= MaxSize);
        return size_prev == 0;
    }
    // only for write
    bool Push(T inst)
    {
        if (Full()) {
            return false;
        }
        buffer.push(inst);
        ++(size_curr);
        return true;
    }
    // only for read
    T Pop()
    {
        assert(!Empty());
        T pop_data = buffer.front();
        buffer.pop();
        --(size_prev);
        return pop_data;
    }
    void Advance()
    {
        // synchronize info
        size_curr = buffer.size();
        size_prev = buffer.size();
        size.Advance();
    }
};


}  // namespace aura
