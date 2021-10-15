#include "../include/stack.hpp"

Stack::Stack() {
}

Stack::Stack(char startSymbol) { content_.push(startSymbol); }

char Stack::getTop() { return content_.top(); }

void Stack::addSymbol(char newSymbol) { content_.push(newSymbol); }

bool Stack::isEmpty() {
  return content_.size() != 0 ? true : false;
}

void Stack::pop() {
  content_.pop();
}

void Stack::updateStack(std::stack<char> newStack) {
  content_ = newStack;
}

std::stack<char> Stack::getStack() { return content_; }
