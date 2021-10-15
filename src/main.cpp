
#include <iostream>

#include "../include/automaton.hpp"

int main() {
  try {
    Automaton apf("examples/APf-3.txt");
    // apf.write();
    apf.verifyString("0110");
  } catch (const std::string& e) {
    std::cerr << e << '\n';
  }
}