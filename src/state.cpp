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
  std::cout << "State " << id_ << std::endl;
}