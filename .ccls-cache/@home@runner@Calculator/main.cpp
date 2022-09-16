#include <iostream>
#include <stack>
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
  std::stack<Token> stack;
  for (Token& t : tokens) {

    // TODO: implement this!

    // Rules
    // 1: if we get one of (+* then push
    // 2: if we get ) then go back and reduce (a) to a
    // 3: if we get number and previous is ( then push
    // 4: if we get number and previous is +* then go back
    //    calculate result and reduce a+b to c
    // 5: anything else is an error

  }

  // Ensure that we only have one item left, and it is a number.
  if (stack.size() != 1 || !stack.top().is_number()) {
    return false;
  }

  // Print the result and return.
  std::cout << stack.top().number() << std::endl;
  return true;
}