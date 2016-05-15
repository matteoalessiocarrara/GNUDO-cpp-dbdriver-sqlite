#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "socket.h"

int current_fd;
fd_set active_fdset;

void util::Socket::connect()
{
  int i,sockfd, clientsz ,y = 1;
  struct sockaddr_in client,server;
  fd_set read_fdset;
  
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd < 0) {
      std::perror("socket");
      std::exit(EXIT_FAILURE);
  }
  
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  
  if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, (char*)&y,sizeof(y)) < 0) {
    std::perror("setsockopt");
    std::exit(EXIT_FAILURE);
  }
  
  if(bind(sockfd,(struct sockaddr*)&server,sizeof(server)) < 0) {
    std::perror("bind");
    std::exit(EXIT_FAILURE);
  }
  
  if(listen(sockfd,5) < 0) {
    std::perror("listen");
    std::exit(EXIT_FAILURE);
  }
  
  FD_ZERO(&active_fdset);
  FD_SET(sockfd,&active_fdset);
  
  while(1) {
    read_fdset = active_fdset;
    
    if(select(FD_SETSIZE,&read_fdset,NULL,NULL,NULL) < 0) {
      std::perror("select");
      std::exit(EXIT_FAILURE);
    }
    
    for(i=0;i<=FD_SETSIZE;++i) {
      if(FD_ISSET(i,&read_fdset)) {
	if(i == sockfd) {
	  clientsz = sizeof(client);
	  current_fd = accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&clientsz);
	  if(current_fd < 0) {
	    std::perror("accept");
	    break;
	  }
	  FD_SET(current_fd,&active_fdset);
	  std::cout << "Someone connected.." << std::endl;
	} else {
	  current_fd = i;
	  mainHandler();
	}
      }
    }
  }
}

char* util::Socket::recvMsg()
{
  char *buf = (char*) malloc(256);
  int rval;
  
  memset(buf,'\0',256);
  if((rval=recv(current_fd,buf,sizeof(buf),0)) < 0) {
    std::perror("read");
    std::sprintf(buf,"recvFailure");
    return buf;
  } else if(rval == 0) {
    close(current_fd);
    FD_CLR(current_fd,&active_fdset);
    std::sprintf(buf,"connDone");
    return buf;
  } 
  
  return buf;
  
}

void util::Socket::sendMsg(const char* __msg_data)
{
  int rval;
  
   std::cout << __msg_data << std::endl;
  
  if((rval=send(current_fd,__msg_data,strlen(__msg_data)+1,0)) == -1) {
    return; //todo
  } else if(rval == 0) {
    return; //todo
  } 
}

void util::Socket::endConnection()
{
  close(current_fd);
  FD_CLR(current_fd,&active_fdset);
}
