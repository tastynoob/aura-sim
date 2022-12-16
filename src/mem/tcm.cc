#include "tcm.hh"

namespace aura
{
TCM::TCM(std::string binfile)
{
    std::ifstream fs;
    fs.open(binfile, std::ios::binary);
    if (!fs.is_open()) {
        throw "cant open file:" + binfile;
    }
    fs.seekg(0, std::ios::end);
    u32 length = fs.tellg();
    tcmSize = length;
    fs.seekg(0, std::ios::beg);
    tcmBuffer = new u8[length + 100];
    fs.read((char*)tcmBuffer, length);
}

void
TCM::Tick(u64 tick)
{
    for (auto it : fromMasterPorts) {
        auto input = it->Input();
        auto output = it->Output();
        if (input->Size() > 0) {
            if (input->address + input->Size() > tcmSize) {
                output->error = true;
                continue;
            } else {
                output->error = false;
            }
            // write tcm
            if (input->write) {
                memcpy(tcmBuffer + input->address, input->wrdBuffer,
                       input->Size());
            } else {  // read tcm
                memcpy(input->wrdBuffer, tcmBuffer + input->address,
                       input->Size());
            }
            output->success = true;
        } else {
            output->error = false;
            output->success = false;
        }
    }
}
}