#pragma once
#include <bits/stdc++.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

namespace aura
{
//the global timing clock
extern u64 global_tick;

}



// config of CPU
#define XLEN 64
#define FETCHWIDTH 4
#define DECODEWIDTH 4
#define RENAMEWIDTH 4

#define IPORTS 1
#define DPORTS 2


//config of memory system