/*
* University of La Laguna
* Grade: Computer ingineering
* Course: 4º
* Subject: Complejidad Computacional
* Turing Machine
* Autor: Carlos Garcia Lezcano
* Gmail: alu0101208268@ull.edu.es
* File state.cpp: Contain the develop of the state methods.
*/

#include "../include/state.hpp"

State::State() {
  id_ = "none";
}

State::State(std::string id) {
  id_ = id;
}

std::string State::getId() {
  return id_;
}

void State::write() {
  std::cout << id_ << std::endl;
}