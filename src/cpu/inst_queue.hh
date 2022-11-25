
#pragma once

#include "base/dyninst.hh"

namespace aura {
// save the instructions of cpu all stage
class InstructionQueue {
  public:
    std::vector<DynInstPtr> inst_queue;
};
}  // namespace aura
