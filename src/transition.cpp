#include "../include/transition.hpp"

Transition::Transition(State initial, char alfabetSymbol, char stackSymbol, State final, std::vector<char> newStackSymbols) {
  initial_ = initial;
  alfabetSymbol_ = alfabetSymbol;
  stackSymbol_ = stackSymbol;
  newStackSymbols_ = newStackSymbols;
  final_ = final;
}

void Transition::write() {
  std::cout << std::endl;
  std::cout << "Initial State: ";
  initial_.write();
  std::cout << "Alfabet symbol: " << alfabetSymbol_ << std::endl;
  std::cout << "Stack symbol: " << stackSymbol_ << std::endl;
  std::cout << "Final State: ";
  final_.write();
  std::cout << "New stack symbols: ";
  for (size_t i = 0; i < newStackSymbols_.size(); i++) {
    std::cout << newStackSymbols_[i] << " ";
  }

  std::cout << std::endl;
  std::cout << std::endl;
}