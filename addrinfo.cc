
#include <iostream>


#include "ip4address.h"


void ShowUsage() {
  std::cout << "Usage:\naddrinfo <www name>\n";
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    ShowUsage();
    return 0;
  }
  Ip4Address ip_address { argv[1] };
  if (ip_address.Error() == 0) {
    std::cout << "Information on address " << argv[1] << std::endl;
    for (unsigned long i = 0; i < ip_address.Len(); ++ i) {
      std::cout << ip_address[i] << std::endl;
    }
  } else {
    std::cerr << ip_address.StrError() << " (" << ip_address.Error() << ")\n";
  }
  return ip_address.Error();
}
