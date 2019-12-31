#pragma once

#include "types.h"


struct in_addr
{
    u32 data;           // 0
};

struct sockaddr
{
    u8 _0;              // 0
    u8 family;          // 1
    u16 port;           // 2
    in_addr address;    // 4
    u8 _8[8];           // 8
};


namespace nn { namespace socket {

Result Initialize(void* memoryPool, u32, u32, s32);

s32 Socket(s32, s32, s32);
s32 Connect(s32 socket,	const sockaddr* address, u32 addressLen);

s32 Send(s32 socket, const void* data, u32 dataLen, s32 unk);
s32 Recv(s32 socket, void* out, u32 outLen, s32 unk);

u16 InetHtons(u16 val);
s32 InetAton(const char* addressStr, in_addr* addressOut);

} }
