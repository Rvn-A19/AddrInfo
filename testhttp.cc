// Check http site utility.
// Make root http request and stream answer to stderr.


#include "ip4address.h"


#include <iostream>


#include <unistd.h>


const std::string simple_http_request_string_ = "GET / HTTP/1.1\r\nHost:";
const std::string close_connection_header_ = "Connection:close";
const std::string rnrn_ = "\r\n\r\n";
const std::string default_host_ = "iana.org";


int main(int argc, char *argv[]) {
  std::string host{ default_host_ };
  if (argc > 1) { 
    host.assign(argv[1]);
  }
  std::string fullrequest(simple_http_request_string_);
  fullrequest.append(host).append("\r\n").append(close_connection_header_); // .append(rnrn_);
  if (argc > 2) {
    fullrequest.append(argv[2]);
  }
  fullrequest.append(rnrn_);
  int sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1) {
    perror("unable to create socket");
    return 1;
  }

  Ip4Address addr { host, "http" };

  if (addr.Error() == 0) {
    bool connected = false;
    struct sockaddr_in target_address;
    memset(&target_address, 0, sizeof(target_address));
    for (unsigned long i = 0; i < addr.Len(); ++ i) {

      std::cout << "connecting to " << host << "(" << addr[i].c_str() << ")" << "\n";

      if (connect(sfd, (const sockaddr *)&addr.GetBinaryAt(i), sizeof(struct sockaddr_in)) == -1) {
        perror("[-] connect");
        if (errno != ECONNREFUSED) {
          return 3;
        }
      } else {
        connected = true;
      }

      write(sfd, fullrequest.c_str(), fullrequest.size());
      int n;
      char buf[512];

      do {
        n = read(sfd, buf, sizeof(buf) - 1);
        if (n < 1) break;
        buf[n] = '\0';
        std::cerr << buf;
      } while (true);
      
      if (connected) break;

    }
  } else {
    std::cerr << addr.StrError() << "\n";
  }
  
  std::cout << "Done\n";
  return 0;
}
