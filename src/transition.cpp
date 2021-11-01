/*
 * University of La Laguna
 * Grade: Computer ingineering
 * Course: 4º
 * Subject: Complejidad Computacional
 * Turing Machine
 * Autor: Carlos Garcia Lezcano
 * Gmail: alu0101208268@ull.edu.es
 * File transition.cpp: Contain the develop of the transition methods.
 */

#include "../include/transition.hpp"

Transition::Transition(State initial, char tapeSymbol, char outputSymbol, State final, char movement) {
  initial_ = initial;
  tapeSymbol_ = tapeSymbol;
  outputSymbol_ = outputSymbol;
  movement_ = movement;
  final_ = final;
}

void Transition::write() {
  std::cout << std::endl;
  std::cout << "Initial State: ";
  initial_.write();
  std::cout << "Tape symbol: " << tapeSymbol_ << std::endl;
  std::cout << "Final State: ";
  final_.write();
  std::cout << "Output Symbol: ";
  std::cout << outputSymbol_ << std::endl;
  std::cout << "Movement: " << movement_ << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}