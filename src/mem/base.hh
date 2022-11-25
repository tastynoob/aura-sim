#pragma once
#include "base/port.hh"


namespace aura
{
//
class BaseMem : public Device
{
  protected:
    std::vector<SlavePort*> fromMasterPorts;

  public:
    void Advance();
    void AddMasterPort(MasterPort* masterPort);
};
}  // namespace
