/*
 * University of La Laguna
 * Grade: Computer ingineering
 * Course: 4º
 * Subject: Complejidad Computacional
 * Turing Machine
 * Autor: Carlos Garcia Lezcano
 * Gmail: alu0101208268@ull.edu.es
 * File turingMachine.hpp: Headers of turing machine
 */
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "state.hpp"
#include "transition.hpp"

#ifndef __TURINGMACHINE__
#define __TURINGMACHINE__

class TuringMachine {
 private:
  std::deque<char> tape_;
  std::vector<State> states_;
  std::vector<char> entryAlfabet_;
  std::vector<char> tapeAlfabet_;
  std::vector<Transition> transitions_;
  State initialState_;
  char white_;
  std::vector<State> acceptanceStates_;
  State currentState_;
  int actualIndex_;

 public:
  TuringMachine(std::string);
  ~TuringMachine();

  void runMachine(std::string);
  bool doTransition();
  bool isAcceptance();
  void showTape();
  void write();
};

#endif