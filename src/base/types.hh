#pragma once
#include "base/opclass.hh"
#include "config.hh"





namespace aura
{

typedef uint64_t Addr;

#if XLEN == 64
typedef uint64_t RegVal;
#endif

enum class RegClass { Integer, Floating };

class RegId
{
  public:
    RegClass regClass;
    u16 regIndex;
};

}  // namespace aura