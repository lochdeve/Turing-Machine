#ifndef _Transition_
#define _Transition_
#include <vector>

#include "state.hpp"

class Transition {
 public:
  Transition(State, char, char, State, std::vector<char>);
  State getInitial() { return initial_; }
  State getFinal() { return final_; }
  char getAlfabetSymbol() { return alfabetSymbol_; }
  char getStackSymbol() { return stackSymbol_; }
  std::vector<char> getNewStackSymbols() { return newStackSymbols_; }
  void write();

 private:
  int id_;
  State initial_;
  State final_;
  char alfabetSymbol_;
  char stackSymbol_;
  std::vector<char> newStackSymbols_;
};

#endif
