/*
* University of La Laguna
* Grade: Computer ingineering
* Course: 4º
* Subject: Complejidad Computacional
* Pushdown Automaton / Automata de pila
* Autor: Carlos Garcia Lezcano
* Gmail: alu0101208268@ull.edu.es
* File automaton.hpp: Contain the headers of the automaton methods.
*/

#ifndef _AUTOMATON_
#define _AUTOMATON_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "stack.hpp"
#include "transition.hpp"

class Automaton {
 public:
  Automaton(std::string);
  ~Automaton();
  void checkState(std::string);
  void checkAlfabet(char, bool);
  std::vector<Transition> getPossibleTransitions();
  bool execution(std::vector<Transition>);
  bool verifyString(std::string);
  void doTransition(Transition&, std::string&);
  bool isAcceptance();

  void write();

 private:
  std::string tape_;
  int tapeShift_;
  Stack stack_;
  State currentState_;
  std::vector<State> states_;
  std::vector<char> stackAlfabet_;
  std::vector<char> entryAlfabet_;
  State initialState_;
  char initialStackSymbol_;
  std::vector<Transition> transitions_;
  std::vector<State> aceptanceStates_;
};
#endif