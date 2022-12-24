#include "cpu/backend/rename.hh"
#include "cpu/o3cpu.hh"

namespace aura
{
Rename::Rename(O3CPU* cpu, TimingBuffer<RenameStruct>* buffer) {}

void
Rename::Tick()
{
    DecodeStruct decodeStruct = cpu->decodeTimingBuffer.Curr();
    renameTimingBuffer->Curr().renameSize = 0;

    while (skidBuffer.size() > 0) {
        DynInstPtr it = skidBuffer.front();
        if (!freeList.Empty()) {
            for (int j = 0; j < it->NumDstRegs(); j++) {
                it->RenameDst(j, RenameDst(it->GetDstRegId(j)));
            }
            for (int j = 0; j < it->NumSrcRegs(); j++) {
                it->RenameSrc(j, RenameSrc(it->GetSrcRegId(j)));
            }
            renameTimingBuffer->Curr()
                .insts[renameTimingBuffer->Curr().renameSize] = it;
            renameTimingBuffer->Curr().renameSize++;
        } else {
            // continue blocking
            renameTimingBuffer->Curr().blocking = true;
            return;
        }
        skidBuffer.pop_front();
    }
    renameTimingBuffer->Curr().blocking = false;


    for (int i = 0; i < decodeStruct.decodeSize; i++) {
        DynInstPtr it = decodeStruct.insts[i];
        if (!freeList.Empty()) {
            for (int j = 0; j < it->NumDstRegs(); j++) {
                it->RenameDst(j, RenameDst(it->GetDstRegId(j)));
            }
            for (int j = 0; j < it->NumSrcRegs(); j++) {
                it->RenameSrc(j, RenameSrc(it->GetSrcRegId(j)));
            }

            renameTimingBuffer->Curr()
                .insts[renameTimingBuffer->Curr().renameSize] = it;
            renameTimingBuffer->Curr().renameSize++;
        } else {
            renameTimingBuffer->Curr().blocking = true;
            skidBuffer.push_back(it);
        }
    }
}
}