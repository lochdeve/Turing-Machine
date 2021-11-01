/*
 * University of La Laguna
 * Grade: Computer ingineering
 * Course: 4º
 * Subject: Complejidad Computacional
 * Turing Machine
 * Autor: Carlos Garcia Lezcano
 * Gmail: alu0101208268@ull.edu.es
 * File turingMachine.cpp: The develop of the turing machine headers
 */

#include "../include/turingMachine.hpp"
TuringMachine::TuringMachine(std::string fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "El archivo no se ha podido abrir" << std::endl;
    std::string error = "El archivo no se ha podido abrir";
    throw error;
  }
  std::string line;
  std::stringstream lineNoComments;
  std::string word;

  // Deleting comments
  while (std::getline(file, line) && line[0] == '#') {
  }
  lineNoComments.clear();

  lineNoComments << line;

  // The set of states
  while (lineNoComments >> word) {
    states_.push_back(State(word));
  }
  lineNoComments.clear();

  std::getline(file, line);
  // Entry alfabet
  lineNoComments << line;

  while (lineNoComments >> word) {
    entryAlfabet_.push_back(word[0]);
  }
  lineNoComments.clear();

  std::getline(file, line);
  // Tape alfabet
  lineNoComments << line;

  while (lineNoComments >> word) {
    tapeAlfabet_.push_back(word[0]);
  }
  lineNoComments.clear();

  std::getline(file, line);
  initialState_ = State(line);
  currentState_ = initialState_;

  std::getline(file, line);
  white_ = line[0];
  for (size_t i = 0; i < 5; i++) {
    tape_.push_back(white_);
  }
  std::getline(file, line);

  lineNoComments << line;

  // The set of states
  while (lineNoComments >> word) {
    acceptanceStates_.push_back(State(word));
  }

  while (std::getline(file, line)) {
    lineNoComments.clear();
    std::string initial, symbol, tapeSymbol, finals, movement;
    lineNoComments << line;

    lineNoComments >> initial;
    lineNoComments >> symbol;
    lineNoComments >> finals;
    lineNoComments >> tapeSymbol;
    lineNoComments >> movement;

    transitions_.push_back(Transition(State(initial), symbol[0], tapeSymbol[0], State(finals), movement[0]));
  }

  file.close();
}
void TuringMachine::runMachine(std::string string) {
  bool finish = false;
  for (size_t i = 0; i < string.size(); i++) {
    tape_.push_back(string[i]);
  }
  currentState_ = initialState_;
  actualIndex_ = 5;
  for (size_t i = 0; i < 5; i++) {
    tape_.push_back(white_);
  }

  while (!finish) {
    finish = doTransition();
  }
  if (isAcceptance()) {
    std::cout << "The string " << string << " is accepted by the Turing Machine" << std::endl;
  } else {
    std::cout << "The string " << string << " is not accepted by the Turing Machine" << std::endl;
  }
  showTape();
  tape_.clear();
  for (size_t i = 0; i < 5; i++) {
    tape_.push_back(white_);
  }
}

TuringMachine::~TuringMachine() {
}

/**
 * This method applies the changes involved in making the transition
 */
bool TuringMachine::doTransition() {
  bool existTransition = false;
  for (int i = 0; i < (int)transitions_.size(); i++) {
    if (transitions_[i].getInitial().getId() == currentState_.getId() && transitions_[i].getTapeSymbol() == tape_[actualIndex_]) {
      tape_[actualIndex_] = transitions_[i].getOutputSymbol();
      existTransition = true;
      // transitions_[i].write();
      currentState_ = transitions_[i].getFinal();
      if (transitions_[i].getMovement() == 'L') {
        if (actualIndex_ == 0) {
          tape_.push_front(white_);
        } else {
          actualIndex_--;
        }

      } else if (transitions_[i].getMovement() == 'R') {
        if (actualIndex_ >= tape_.size() - 1) {
          tape_.push_front(white_);
        } else {
          actualIndex_++;
        }
      }
    }
  }
  return !existTransition;
}

/**
 * Verify if the current state is an acceptance state
 */
bool TuringMachine::isAcceptance() {
  for (size_t i = 0; i < acceptanceStates_.size(); i++) {
    if (acceptanceStates_[i].getId() == currentState_.getId()) {
      return true;
    }
  }
  return false;
}

void TuringMachine::write() {
  std::cout << "States: " << std::endl;
  for (size_t i = 0; i < states_.size(); i++) {
    states_[i].write();
  }
  std::cout << std::endl;

  std::cout << "Initial State: ";
  initialState_.write();

  std::cout << "Entry alfabet: ";
  for (size_t i = 0; i < entryAlfabet_.size(); i++) {
    std::cout << entryAlfabet_[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Tape alfabet: ";
  for (size_t i = 0; i < tapeAlfabet_.size(); i++) {
    std::cout << tapeAlfabet_[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "White symbol: "
            << "\"";
  std::cout << white_ << "\"" << std::endl;

  std::cout << "Aceptances States: ";
  for (size_t i = 0; i < acceptanceStates_.size(); i++) {
    acceptanceStates_[i].write();
  }

  std::cout << std::endl;
  for (size_t i = 0; i < transitions_.size(); i++) {
    std::cout << "Transition " << i + 1 << std::endl;
    transitions_[i].write();
  }
}

void TuringMachine::showTape() {
  std::cout << "The final tape is: ";

  for (auto it = tape_.begin(); it != tape_.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}