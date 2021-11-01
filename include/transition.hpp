/*
 * University of La Laguna
 * Grade: Computer ingineering
 * Course: 4º
 * Subject: Complejidad Computacional
 * Turing Machine
 * Autor: Carlos Garcia Lezcano
 * Gmail: alu0101208268@ull.edu.es
 * File transition.hpp: Contain the headers of the transition methods.
 */

#ifndef _Transition_
#define _Transition_
#include <vector>

#include "state.hpp"

class Transition {
 public:
  Transition(State, char, char, State, char);
  State getInitial() { return initial_; }
  State getFinal() { return final_; }
  char getTapeSymbol() { return tapeSymbol_; }
  char getOutputSymbol() { return outputSymbol_; }
  char getMovement() { return movement_; }
  void write();

 private:
  int id_;
  State initial_;
  State final_;
  char tapeSymbol_;
  char outputSymbol_;
  char movement_;
};

#endif
