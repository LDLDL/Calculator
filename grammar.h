//
// Created by yuki on 2020/11/11.
//

#ifndef GANALYZE__GRAMMAR_H_
#define GANALYZE__GRAMMAR_H_

#include <list>
#include <stack>
#include "dfa.h"

/*  0) E'->#E#
    1) E->E+T
    2) E->E-T
    3) E->T
    4) T->T*F
    5) T->T/F
    6) T->F
    7) F->(E)
    8) F->I
    9) I->十进制实数|十进制整数|十六进制实数|十六进制整数|八进制实数|八进制整数
*/

namespace grammar{

class GrammarAnalyze{
 private:
  static const std::unordered_map<char, std::unordered_map<char, char>> vt;

  dfa::NumbericDfa d;

  std::list<char> as;

  std::stack<double> ns;
 public:
  double value = 0;

  bool accept = false;

  GrammarAnalyze();

  explicit GrammarAnalyze(std::string &instr);

  void reset(std::string &in);

  void grammar_analyze();
};

}

#endif //GANALYZE__GRAMMAR_H_
