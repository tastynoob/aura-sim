#pragma once
#include "base/dyninst.hh"
#include "base/types.hh"

namespace aura
{
struct FetchQueEntry
{
    Addr basePC;
    
};
struct FetchStruct;
struct DecodeStruct
{
    u8 decodeSize;
    DynInstPtr insts[DECODEWIDTH];
};
struct RenameStruct
{
    u8 renameSize;
    DynInstPtr insts[RENAMEWIDTH];
};
struct IssueStruct
{
};

struct ExecuteStruct
{
};

struct CommitStruct
{
};

}  // namespace aura
