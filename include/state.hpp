/*
* University of La Laguna
* Grade: Computer ingineering
* Course: 4º
* Subject: Complejidad Computacional
* Turing Machine
* Autor: Carlos Garcia Lezcano
* Gmail: alu0101208268@ull.edu.es
* File state.hpp: Contain the headers of the state methods.
*/

#ifndef _STATE_
#define _STATE_

#include <iostream>
#include <string>

class State {
 public:
  State();
  State(std::string);
  std::string getId();

  void write();

 private:
  std::string id_;
};

#endif