#include <iostream>
#include "grammar.h"

int main() {
  std::string instr;
  grammar::GrammarAnalyze ga;

  do{
    std::cout << "> ";
    std::cin >> instr;
    ga.reset(instr);
    ga.grammar_analyze();
    if (ga.accept) {
      std::cout << "正确句子." << std::endl;
      std::cout << "========================" << std::endl;
      std::cout << "结果: " << ga.value << '\n' << std::endl;
    }
    else {
      std::cout << std::endl;
    }
  } while (true);

  return 0;
}
