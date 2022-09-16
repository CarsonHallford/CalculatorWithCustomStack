#include <iostream>
#include <string>
#include <vector>

#include "token.h"

bool solve(std::vector<Token> tokens);

int main() {
  std::string expression;
  std::cin >> expression;
  std::vector<Token> tokens = tokens_from_expression(expression);
  if (!solve(tokens)) {
    std::cout << "error\n";
  }
}

bool solve(std::vector<Token> tokens) {
  // TODO: implement!
  return true;
}