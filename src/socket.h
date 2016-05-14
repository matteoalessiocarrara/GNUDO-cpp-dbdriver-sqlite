#ifndef __SOCKET_SERVER_H
#define __SOCKET_SERVER_H

#include "gnudo_nsp.h"

class gnudo::SocketServer 
{
public:
  SocketServer(const char* ipaddr="127.0.0.1", 
	       const unsigned int port=4747);
  ~SocketServer();
  int launchServer();
  int getData();
  void sendData();
  
private:
  int sockfd;
  const char* _ipaddr;
  const char* _port;
};

#endif //__SOCKET_SERVER_H