#ifndef __SOCKET_H
#define __SOCKET_H

#define PORT 9999

#include "gnudo_nsp.h"

namespace util 
{
  namespace Socket 
  {
    void connect();
    char* recvMsg();
    void sendMsg(const char* __msg_data);
    void endConnection();
  }
}

extern void mainHandler();

#endif //__SOCKET_H