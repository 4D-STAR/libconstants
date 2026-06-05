#include "fourdst/constants/const.h"
#include <iostream>

int main() {
  fourdst::constant::Constants& C = fourdst::constant::Constants::getInstance();
  
  std::cout << "Speed of light is " << C.get("c") << std::endl;
  std::cout << "All avalible constants are: ";

  for (const auto& key : C.keys()) {
    std::cout << "\t " << key << ": " << C[key];
  }
}
