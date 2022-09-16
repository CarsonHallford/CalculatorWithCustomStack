// Peer Reviewed by Kevin Fogle
// I receieved help via https://pages.cs.wisc.edu/~siff/CS367/Notes/stacks.html
// for stack refresher and efficiency
// Written by Carson Hallford
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "linked_list.h"
#include "token.h"

bool solve(std::vector<Token> tokens);

int main() {
  std::string expression;
  std::cin >> expression;  // O(1)
  std::vector<Token> tokens = tokens_from_expression(expression);
  if (!solve(tokens)) {
    std::cout << "error\n";  // O(1)
  }
}
// O(1)
bool solve(std::vector<Token> tokens) {
  // std::stack<Token> stack;
  LinkedList<Token> stack;
  stack.head = new Node<Token>();  // O(1)

  // O(n)
  for (Token &t : tokens) {
    // TODO: implement this!
    // Rules
    // 1: if we get one of (+* then push
    // O(1)
    if (t.is_left_paren() || t.is_add() || t.is_multiply()) {
      stack.stack_push(t);
    }
    // 2: if we get ) then go back and reduce (a) to a
    // O(1)
    else if (t.is_right_paren()) {
      if (stack.stack_size() == 0) {
        return false;
      }

      // O(1)
      else {
        Token tt = stack.stack_top();
        stack.stack_pop();             // O(1)
        if (stack.stack_size() > 1 &&  // O(n)
            (stack.stack_top().is_add() || stack.stack_top().is_multiply())) {
          // O(1)
          if (stack.stack_top().is_add()) {
            stack.stack_pop();
            Token num2 = (stack.stack_top().number() + tt.number());
            stack.stack_pop();
            stack.stack_pop();
            stack.stack_push(num2);
            // O(1)
          } else {
            stack.stack_pop();
            Token num2 = (stack.stack_top().number() * tt.number());
            stack.stack_pop();
            stack.stack_pop();
            stack.stack_push(num2);
          }
        } else {
          //(a) -> a
          if (stack.stack_size() > 0) {
            stack.stack_pop();
          } else {
            return false;
          }
          stack.stack_push(tt);
          if (stack.stack_size() >= 3) {
            Token oldTop = stack.stack_top();
            stack.stack_pop();
            if (stack.stack_top().is_add() || stack.stack_top().is_multiply()) {
              if (stack.stack_top().is_add()) {
                stack.stack_pop();
                Token sum = (oldTop.number() + stack.stack_top().number());
                stack.stack_pop();
                stack.stack_push(sum);
                // O(1)
              } else {
                stack.stack_pop();
                Token product = (oldTop.number() * stack.stack_top().number());
                stack.stack_pop();
                stack.stack_push(product);
              }

            } else {
              stack.stack_push(oldTop);  // O(1)
            }
          }
        }
      }
    }
    // 3: if we get number and stack is empty then push
    else if (t.is_number() && stack.stack_size() == 0) {
      stack.stack_push(t);  // O(1)
    }
    // 4: if we get number and previous is ( then push
    else if (t.is_number() && stack.stack_top().is_left_paren()) {
      stack.stack_push(t);  // O(1)
    }
    // 5: if we get number and previous is +* then go back
    // O(1)
    else if (t.is_number() &&
             (stack.stack_top().is_add() || stack.stack_top().is_multiply())) {
      // O(1)
      if (stack.stack_top().is_add()) {
        stack.stack_pop();
        Token sum = (stack.stack_top().number() + t.number());
        stack.stack_pop();
        stack.stack_push(sum);
        // O(1)
      } else {
        stack.stack_pop();
        Token product = (stack.stack_top().number() * t.number());
        stack.stack_pop();
        stack.stack_push(product);
      }
      //    calculate result and reduce a+b to c
    }
    // 6: anything else is an error
  }

  // Ensure that we only have one item left, and it is a number.
  if (stack.stack_size() != 1 || !stack.stack_top().is_number()) {
    return false;
  }

  // Print the result and return.
  std::cout << stack.stack_top().number() << std::endl;  // O(1)
  return true;
}