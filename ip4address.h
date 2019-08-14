/*
  Convert dns name - header.
 */
#ifndef IP4ADDRESS_H_
#define IP4ADDRESS_H_


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


#include <cstring>
#include <vector>
#include <string>


typedef struct addrinfo * PAddrInfo;


class Ip4Address {

public:
  Ip4Address(const std::string & name);
  ~Ip4Address();
  const std::string & operator [](unsigned long idx) const;
  unsigned long Len();
  int Error();
  const char * StrError();

private:
  const std::string null_string_ = "";
  std::vector<std::string> addresses;
  char ipstr_address[INET_ADDRSTRLEN];
  struct sockaddr_in *ip_pointer;
  struct addrinfo hints;
  PAddrInfo head, elem;
  unsigned long len;
  int err;

};


#endif // IP4ADDRESS_H_
