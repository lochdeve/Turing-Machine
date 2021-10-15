/*
* University of La Laguna
* Grade: Computer ingineering
* Course: 4º
* Subject: Complejidad Computacional
* Pushdown Automaton / Automata de pila
* Autor: Carlos Garcia Lezcano
* Gmail: alu0101208268@ull.edu.es
* File automaton.cpp: Contain the develop of the automaton methods.
*/

#include "../include/automaton.hpp"

Automaton::~Automaton() {}

Automaton::Automaton(std::string fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "El archivo no se ha podido abrir" << std::endl;
    std::string error = "El archivo no se ha podido abrir";
    throw error;
  }
  std::string line;
  std::stringstream lineNoComments;
  std::string word;
  while (std::getline(file, line) && line[0] == '#') {
  }
  lineNoComments.clear();

  lineNoComments << line;
  while (lineNoComments >> word) {
    states_.push_back(State(word));
  }
  std::getline(file, line);
  lineNoComments.clear();

  lineNoComments << line;

  while (lineNoComments >> word) {
    entryAlfabet_.push_back(word[0]);
  }

  std::getline(file, line);
  lineNoComments.clear();

  lineNoComments << line;

  while (lineNoComments >> word) {
    stackAlfabet_.push_back(word[0]);
  }
  file >> word;

  initialState_ = State(word);
  checkState(word);
  std::getline(file, line);
  std::getline(file, line);
  initialStackSymbol_ = line[0];
  stack_.addSymbol(initialStackSymbol_);

  std::getline(file, line);
  lineNoComments.clear();

  lineNoComments << line;
  while (lineNoComments >> word) {
    aceptanceStates_.push_back(State(word));
    checkState(word);
  }
  while (getline(file, line)) {
    lineNoComments.clear();
    lineNoComments << line;
    lineNoComments >> word;

    std::string start = word;
    checkState(start);
    lineNoComments >> word;

    char alfabetSymbol = word[0];
    checkAlfabet(word[0], false);
    lineNoComments >> word;

    char stackSymbol = word[0];
    checkAlfabet(word[0], true);

    lineNoComments >> word;

    std::string finalState = word;
    checkState(finalState);

    std::vector<char> stackSymbols;
    while (!lineNoComments.eof()) {
      lineNoComments >> word;
      stackSymbols.push_back(word[0]);
    }
    transitions_.push_back(Transition(State(start), alfabetSymbol, stackSymbol, State(finalState), stackSymbols));
  }
  currentState_ = initialState_;
  file.close();
}

void Automaton::write() {
  std::cout << "States: " << std::endl;
  for (size_t i = 0; i < states_.size(); i++) {
    states_[i].write();
  }
  std::cout << std::endl;

  std::cout << "Initial State: ";
  initialState_.write();

  std::cout << "Aceptances States: ";
  for (size_t i = 0; i < aceptanceStates_.size(); i++) {
    aceptanceStates_[i].write();
  }

  std::cout << "Entry alfabet: ";
  for (size_t i = 0; i < entryAlfabet_.size(); i++) {
    std::cout << entryAlfabet_[i] << " ";
  }

  std::cout << "Stack alfabet: ";
  for (size_t i = 0; i < stackAlfabet_.size(); i++) {
    std::cout << stackAlfabet_[i] << " ";
  }
  std::cout << std::endl;
  for (size_t i = 0; i < transitions_.size(); i++) {
    std::cout << "Transition " << i + 1 << std::endl;
    transitions_[i].write();
  }
}

void Automaton::checkState(std::string candidate) {
  bool exist = false;
  for (size_t i = 0; i < states_.size(); i++) {
    if (states_[i].getId() == candidate) {
      exist = true;
      break;
    }
  }
  if (!exist) {
    std::string error = "The state " + candidate + " from one of the transitions do not exist in this Automaton";
    throw error;
  }
}

void Automaton::checkAlfabet(char candidate, bool stack) {
  bool exist = false;
  std::vector<char> alfabet = entryAlfabet_;
  if (stack) {
    alfabet = stackAlfabet_;
  }
  for (size_t i = 0; i < alfabet.size(); i++) {
    if (alfabet[i] == candidate || candidate == '.') {
      exist = true;
      break;
    }
  }
  std::string candidatePrint = "";
  candidatePrint += candidate;
  if (!exist) {
    std::string error = "The symbol " + candidatePrint + " from one of the transitions do not exist in this Automaton";
    throw error;
  }
}

std::vector<Transition> Automaton::getPossibleTransitions() {
  std::vector<Transition> transitions;
  char correctSymbol = tape_[tapeShift_];
  if (tapeShift_ > (int)tape_.size()) {
    correctSymbol = '.';
  }
  for (size_t i = 0; i < transitions_.size(); i++) {
    if (transitions_[i].getInitial().getId() == currentState_.getId() && stack_.getTop() == transitions_[i].getStackSymbol() && (transitions_[i].getAlfabetSymbol() == correctSymbol || transitions_[i].getAlfabetSymbol() == '.')) {
      transitions.push_back(transitions_[i]);
    }
  }
  return transitions;
}

bool Automaton::verifyString(std::string cadena) {
  if (cadena[0] == '.') {
    tape_ = "";
  } else {
    tape_ = cadena;
  }
  tapeShift_ = 0;
  if (execution(getPossibleTransitions())) {
    std::cout << "Se acepta la cadena" << std::endl;
  } else {
    std::cout << "No acepta la cadena" << std::endl;
  }
  return true;
}

bool Automaton::execution(std::vector<Transition> possibleTransitions) {
  State auxState = currentState_;
  std::stack<char> stackCopy = stack_.getStack();
  int shift = tapeShift_;

  if (possibleTransitions.size() != 0 && tapeShift_ <= (int)tape_.size()) {
    doTransition(possibleTransitions[possibleTransitions.size() - 1], tape_);
    possibleTransitions.pop_back();
    if (execution(getPossibleTransitions())) {
      return true;
    }
    currentState_ = auxState;
    stack_.updateStack(stackCopy);
    tapeShift_ = shift;
    if (execution(possibleTransitions)) {
      return true;
    }
  } else if (tapeShift_ == (int)tape_.size() && isAcceptance()) {
    return true;
  }

  return false;
}
/*
bool Automaton::execution() {
  std::vector<Transition> possibleTransitions;
  std::string lastCadena = tape_;
  std::cout << tape_ << " " << tapeShift_ << std::endl;
  possibleTransitions = getPossibleTransitions(currentState_, stack_.getTop(), tape_[tapeShift_]);

  std::cout << "Current State: ";
  currentState_.write();
  State auxState = currentState_;
  std::stack<char> stackCopy = stack_.getStack();
  int shift = tapeShift_;

  if (possibleTransitions.size() != 0 && tapeShift_ <= (int)tape_.size()) {
    //std::cout << "erntra aqui production " << possibleTransitions.size() << std::endl;
    std::cout << "auxState ";
    auxState.write();
    doTransition(possibleTransitions[possibleTransitions.size() - 1], tape_);
    possibleTransitions.pop_back();
    execution();
    std::cout << "auxState2 ";
    auxState.write();
    currentState_ = auxState;
    stack_.updateStack(stackCopy);
    tapeShift_ = shift;
    std::cout << "size possible: " << possibleTransitions.size() << std::endl;
    //possibleTransitions[0].write();
    if (possibleTransitions.size() == 0 && tapeShift_ < (int)tape_.size()) {
      std::cout << "erntra aqui ????????????????  " << std::endl;
      std::cout << "auxState marhca atras ";

      possibleTransitions = getPossibleTransitions(currentState_, stack_.getTop(), tape_[tapeShift_]);
      doTransition(possibleTransitions[possibleTransitions.size() - 1], tape_);
      possibleTransitions.pop_back();
      execution();
    }
  } else if (possibleTransitions.size() != 0 && tapeShift_ >= (int)tape_.size()) {
    return true;
  } else if (isAcceptance() && tapeShift_ >= (int)tape_.size()) {
    return true;
  }

  return false;
}
*/
void Automaton::doTransition(Transition& transition, std::string& cadena) {
  if (transition.getAlfabetSymbol() != '.') {
    tapeShift_++;
  }
  stack_.pop();
  //transition.write();
  for (int i = transition.getNewStackSymbols().size() - 1; i >= 0; i--) {
    if (transition.getNewStackSymbols()[i] != '.') {
      stack_.addSymbol(transition.getNewStackSymbols()[i]);
    }
  }
  currentState_ = transition.getFinal();
}

bool Automaton::isAcceptance() {
  for (size_t i = 0; i < aceptanceStates_.size(); i++) {
    if (aceptanceStates_[i].getId() == currentState_.getId()) {
      return true;
    }
  }
  return false;
}
