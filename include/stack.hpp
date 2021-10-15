#ifndef _Stack_
#define _Stack_
#include <stack>
#include <string>

class Stack {
 public:
  Stack();
  Stack(char);

  char getTop();
  void addSymbol(char);
  bool isEmpty();
  void pop();
  void updateStack(std::stack<char>);
  std::stack<char> getStack();

 private:
  std::stack<char> content_;
};

#endif