#pragma once
#include "mem/base.hh"

namespace aura
{

class TCM : public BaseMem
{
    u8* tcmBuffer;

  public:
    TCM(std::string binfile);
    void Tick(u64 tick);
};

}  // namespace aura
