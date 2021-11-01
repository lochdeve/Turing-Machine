/*
* University of La Laguna
* Grade: Computer ingineering
* Course: 4º
* Subject: Complejidad Computacional
* Turing Machine
* Autor: Carlos Garcia Lezcano
* Gmail: alu0101208268@ull.edu.es
* File main.cpp: The main program
*/
#include <iostream>

#include "../include/turingMachine.hpp"

int main() {
  try {
    std::string fileName;
    std::cout << "Introducir el nombre del archivo: ";
    std::cin >> fileName;
    TuringMachine machine(fileName);
    std::string string;
    int option = 0;
    do {
      std::cout << std::endl;
      std::cout << "----------Execution Menu----------" << std::endl;
      std::cout << "1.Test a string" << std::endl;
      std::cout << "2.Show the resume of the automaton" << std::endl;
      std::cout << "3.Exit" << std::endl;
      std::cout << "  Option: ";
      std::cin >> option;
      std::cout << std::endl;

      switch (option) {
        case 1: {
          std::cout << "Introduce a string to test: ";
          std::cin >> string;
          machine.runMachine(string);
        } break;
        case 2:
          machine.write();
          break;
        case 3:
          std::cout << "Closing the execution..." << std::endl;
          break;
        default:
          std::cout << "The option entered does not exist please enter a valid one" << std::endl;
          break;
      }

    } while (option != 3);
  } catch (const std::string& e) {
    std::cerr << e << '\n';
  }
}