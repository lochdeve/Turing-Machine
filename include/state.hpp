#ifndef _STATE_
#define _STATE_

#include <iostream>
#include <string>

class State {
 public:
  State();
  State(std::string);
  std::string getId();

  void write();

 private:
  std::string id_;
};

#endif