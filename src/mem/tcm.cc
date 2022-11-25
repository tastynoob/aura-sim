#include "tcm.hh"

namespace aura
{
TCM::TCM(std::string binfile)
{
    std::ifstream fs;
    fs.open(binfile);
    if (!fs.is_open()) {
        throw "cant open file:" + binfile;
    }
    fs.seekg(0, std::ios::end);  // go to the end
    u32 length = fs.tellg();
    fs.seekg(0, std::ios::beg);
    tcmBuffer = new u8[length + 100];
    fs.read((char*)tcmBuffer, length);
}

void
TCM::Tick(u64 tick)
{
    for (auto it : fromMasterPorts) {
        if (it->Input()->size > 0) {
            // write tcm
            if (it->Input()->write) {
                memcpy(tcmBuffer + it->Input()->address,
                       it->Input()->wrdBuffer, it->Input()->size);
            } else {  // read tcm
                memcpy(it->Input()->wrdBuffer,
                       tcmBuffer + it->Input()->address, it->Input()->size);
            }
            it->Output()->success = true;
        } else {
            it->Output()->success = false;
        }
    }
}
}