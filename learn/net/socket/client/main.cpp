/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yt (fndisme), fndisme@163.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
  struct sockaddr_in sa;
  int res;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (-1 == SocketFD) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }

  memset(&sa, 0, sizeof sa);

  sa.sin_family = AF_INET;
  sa.sin_port = htons(2222);
  res = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

  if (-1 == connect(SocketFD, (struct sockaddr*)&sa, sizeof sa)) {
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  char buffer[512];
	int totalRead = 0;
  for (;;) {
    int readSize = 0;
    readSize = read(SocketFD, buffer + totalRead, sizeof(buffer) - totalRead);
    if (readSize == 0) {
      // read all
      break;
    } else if (readSize == -1) {
      perror("read failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
		totalRead += readSize;
  }
	buffer[totalRead] = 0;
	printf("get from server: %s\n", buffer);
  /*  perform read write operations ... */

  (void)shutdown(SocketFD, SHUT_RDWR);
  close(SocketFD);
  return EXIT_SUCCESS;
}
