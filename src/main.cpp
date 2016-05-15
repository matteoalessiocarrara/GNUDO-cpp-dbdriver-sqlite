#include<iostream>

#include "socket.h"

void mainHandler() {
  char *msg = util::Socket::recvMsg();
  std::cout << msg << std::endl;
  
  util::Socket::sendMsg("ciao");
}

int main()
{
  util::Socket::connect();
  
  std::cout << "hello" << std::endl;

  return 0;
}
