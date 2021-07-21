//
// Created by yuki on 2020/10/28.
//

#ifndef GANALIZE__DFA_H_
#define GANALIZE__DFA_H_

/*   9) I->十进制实数|十进制整数|十六进制实数|十六进制整数|八进制实数|八进制整数
    10) 十进制实数 -> (0|(1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9) *).(0|1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)*
    11) 八进制实数 -> 0(0|1|2|3|4|5|6|7)(0|1|2|3|4|5|6|7)*.(0|1|2|3|4|5|6|7)(0|1|2|3|4|5|6|7)*
    12) 十六进制实数 -> 0x(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)*.(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)*
    13) 十进制整数 -> 0|(1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)*
    14) 八进制整数 -> 0(0|1|2|3|4|5|6|7)(0|1|2|3|4|5|6|7)*
    15)十六进制整数 -> 0x(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)(0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f)*
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>
#include <cmath>

namespace dfa{

class NumbericDfa{
 private:
  static const char NOT_ACCEPT = 0x00;
  const char VALUE = 'i';

  static char cf_S(char alpha);
  static char cf_Y(char alpha);
  static char cf_A(char alpha);
  static char cf_B(char alpha);
  static char cf_C(char alpha);
  static char cf_D(char alpha);
  static char cf_E(char alpha);
  static char cf_F(char alpha);
  static char cf_G(char alpha);
  static char cf_H(char alpha);
  static char cf_I(char alpha);
  static char cf_J(char alpha);
  static char cf_K(char alpha);

  static const std::unordered_map<char, std::function<char(char)>> change_function_map;

  static const std::unordered_map<char, std::string> final_stat_str;

  static inline bool is_operator(char alpha);

  std::string instr;

 public:
  bool error = false;

  std::queue<std::pair<char, double>> world_que;

  NumbericDfa();

  explicit NumbericDfa(std::string &in);

  void reset(std::string &in);

  void print_block(std::size_t &start, std::size_t offset, char stat);

  void print_queue();

  void world_analyse();
};

}

#endif //GANALIZE__DFA_H_
