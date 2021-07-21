//
// Created by yuki on 2020/10/28.
//

#include "dfa.h"

using namespace dfa;

char dfa::NumbericDfa::cf_S(char alpha) {
  if (alpha == '0')
    return 'A';
  else if (alpha > '0' and alpha <= '9')
    return 'B';
  else if (alpha == '+' or alpha == '-' or alpha == '*' or alpha == '/' or alpha == '(' or alpha == ')')
    return 'Y';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_Y(char alpha) {
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_B(char alpha) {
  if (alpha >= '0' and alpha <= '9')
    return 'B';
  else if (alpha == '.')
    return 'J';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_A(char alpha) {
  if (alpha >= '0' and alpha <= '7')
    return 'C';
  else if (alpha == '.')
    return 'J';
  else if (alpha == 'x')
    return 'F';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_J(char alpha){
  if (alpha >= '0' and alpha <= '9')
    return 'K';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_K(char alpha){
  if (alpha >= '0' and alpha <= '9')
    return 'K';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_C(char alpha){
  if (alpha >= '0' and alpha <= '7')
    return 'C';
  else if (alpha == '.')
    return 'D';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_D(char alpha){
  if (alpha >= '0' and alpha <= '7')
    return 'E';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_E(char alpha){
  if (alpha >= '0' and alpha <= '7')
    return 'E';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_F(char alpha){
  if ((alpha >= '0' and alpha <= '9') or (alpha >= 'a' and alpha <= 'f') or (alpha >= 'A' and alpha <= 'F'))
    return 'G';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_G(char alpha){
  if ((alpha >= '0' and alpha <= '9') or (alpha >= 'a' and alpha <= 'f') or (alpha >= 'A' and alpha <= 'F'))
    return 'G';
  else if (alpha == '.')
    return 'H';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_H(char alpha){
  if ((alpha >= '0' and alpha <= '9') or (alpha >= 'a' and alpha <= 'f') or (alpha >= 'A' and alpha <= 'F'))
    return 'I';
  return NOT_ACCEPT;
}

char dfa::NumbericDfa::cf_I(char alpha){
  if ((alpha >= '0' and alpha <= '9') or (alpha >= 'a' and alpha <= 'f') or (alpha >= 'A' and alpha <= 'F'))
    return 'I';
  return NOT_ACCEPT;
}

bool dfa::NumbericDfa::is_operator(char alpha) {
  return (alpha == '(' or alpha == ')' or alpha == '+' or alpha == '-' or alpha == '*' or alpha == '/');
}

const std::unordered_map<char, std::function<char(char)>> dfa::NumbericDfa::change_function_map{
    {'S', dfa::NumbericDfa::cf_S},
    {'Y', dfa::NumbericDfa::cf_Y},
    {'A', dfa::NumbericDfa::cf_A},
    {'B', dfa::NumbericDfa::cf_B},
    {'C', dfa::NumbericDfa::cf_C},
    {'D', dfa::NumbericDfa::cf_D},
    {'E', dfa::NumbericDfa::cf_E},
    {'F', dfa::NumbericDfa::cf_F},
    {'G', dfa::NumbericDfa::cf_G},
    {'H', dfa::NumbericDfa::cf_H},
    {'I', dfa::NumbericDfa::cf_I},
    {'J', dfa::NumbericDfa::cf_J},
    {'K', dfa::NumbericDfa::cf_K}
};

const std::unordered_map<char, std::string> dfa::NumbericDfa::final_stat_str{
    {'Y', std::string("运算符")},
    {'B', std::string("十进制整数")},
    {'A', std::string("十进制整数")},
    {'K', std::string("十进制实数")},
    {'C', std::string("八进制整数")},
    {'E', std::string("八进制实数")},
    {'G', std::string("十六进制整数")},
    {'I', std::string("十六进制实数")}
};

dfa::NumbericDfa::NumbericDfa(std::string &in):instr(in){

}

dfa::NumbericDfa::NumbericDfa() {

}

void dfa::NumbericDfa::reset(std::string &in) {
  instr = in;
  while(not world_que.empty()){
    world_que.pop();
  }
}

void dfa::NumbericDfa::print_block(std::size_t &start,
                                   std::size_t offset,
                                   char stat) {
  try{
    const auto& ty = final_stat_str.at(stat);
    std::cout << ty << " " << instr.substr(start, offset) << std::endl;
  } catch (std::out_of_range &o) {
    std::cout << "错误数据 " << instr.substr(start, offset) << std::endl;
  }
}

inline double ostod(std::string s){
  double _x = 0;
  s = s.substr(1);
  int xsw = 0;
  for (auto j : s) {
    if(xsw != 0){
      _x += (j - '0') * pow(8, -xsw);
      xsw++;
    }
    else{
      if(j != '.'){
        _x = _x * 8 + (j - '0');
      }
      else{
        xsw++;
      }
    }
  }
  return _x;
}

void dfa::NumbericDfa::world_analyse() {
  std::size_t _l = instr.size();
  std::size_t _start = 0;
  std::size_t index = 0;
  char dfa_status;

  for(; index < _l; ++index){
    if(is_operator(instr[index])){
      dfa_status = 'S';

      for(std::size_t i = _start; i < index; ++i){
        const auto &change_func = change_function_map.at(dfa_status);
        dfa_status = change_func(instr[i]);
        if(dfa_status == NOT_ACCEPT) {
          this->error = true;
          break;
        }
      }

      if(index != _start){
        try{
          std::string _i = instr.substr(_start, index - _start);
          if(dfa_status == 'C' or dfa_status == 'E'){
            world_que.push(std::pair<char, double>(VALUE, ostod(_i)));
          }
          else{
            world_que.push(std::pair<char, double>(VALUE, std::stod(_i)));
          }
        }
        catch (std::exception &e) {

        }
        print_block(_start, index - _start, dfa_status);
      }

      try{
        world_que.push(std::pair<char, double>(instr[index], 0));
      }
      catch (std::exception &e) {

      }
      std::cout << "运算符 " << instr[index] << std::endl;

      _start = index + 1;
    }
  }
  if(not is_operator(instr[index])){
    dfa_status = 'S';

    for(std::size_t i = _start; i < index; ++i){
      const auto &change_func = change_function_map.at(dfa_status);
      dfa_status = change_func(instr[i]);
      if(dfa_status == NOT_ACCEPT) {
        this->error = true;
        break;
      }
    }

    if(index != _start){
      try{
        std::string _i = instr.substr(_start, index - _start);
        if(dfa_status == 'C' or dfa_status == 'E'){
          world_que.push(std::pair<char, double>(VALUE, ostod(_i)));
        }
        else{
          world_que.push(std::pair<char, double>(VALUE, std::stod(_i)));
        }
      }
      catch (std::exception &e) {

      }
      print_block(_start, index - _start, dfa_status);
    }
  }

  world_que.push(std::pair<char, double>('#', 0));
}

void dfa::NumbericDfa::print_queue() {
  while(not world_que.empty()){
    auto item = world_que.front();
    std::cout << item.first << " " << item.second << std::endl;
    world_que.pop();
  }
}