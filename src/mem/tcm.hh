#pragma once
#include "mem/base.hh"

namespace aura
{

class TCM : public BaseMem
{
    u8* tcmBuffer;
    u32 tcmSize;

  public:
    TCM(std::string binfile);
    void Tick(u64 tick);
};

}  // namespace aura
