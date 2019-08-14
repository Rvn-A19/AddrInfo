/*
 * Convert dns name - implementation.
*/


#include "ip4address.h"


Ip4Address::Ip4Address(const std::string & name) {
  head = nullptr;
  elem = nullptr;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  err = getaddrinfo(name.c_str(), nullptr, &hints, &head);
  if (err == 0) {
    elem = head;
    for (; elem; elem = elem->ai_next) {
      ip_pointer = reinterpret_cast<struct sockaddr_in *>(elem->ai_addr);
      inet_ntop(elem->ai_family, &ip_pointer->sin_addr, ipstr_address, elem->ai_family == AF_INET ? sizeof(struct sockaddr_in) :
                                                                                                    sizeof(struct sockaddr_in6));
      addresses.push_back(ipstr_address);
    }
  }
  len = addresses.size();
}


Ip4Address::~Ip4Address() {
  if (head) {
    freeaddrinfo(head);
  }
}


const std::string & Ip4Address::operator[](unsigned long idx) const {
  if (idx >= len) return null_string_;
  return addresses[idx];
}


unsigned long Ip4Address::Len() {
  return len;
}


int Ip4Address::Error() {
  return err;
}


const char * Ip4Address::StrError() {
  return gai_strerror(err);
}

