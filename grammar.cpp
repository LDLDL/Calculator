//
// Created by yuki on 2020/11/11.
//

#include "grammar.h"

const std::unordered_map<char, std::unordered_map<char, char>> grammar::GrammarAnalyze::vt{
    {'+', {
        {'+', '>'},
        {'-', '>'},
        {'*', '>'},
        {'/', '>'},
        {'(', '<'},
        {')', '>'},
        {'i', '>'},
        {'#', '<'}
      }
    },
    {'-', {
        {'+', '>'},
        {'-', '>'},
        {'*', '>'},
        {'/', '>'},
        {'(', '<'},
        {')', '>'},
        {'i', '>'},
        {'#', '<'}
      }
    },
    {'*', {
        {'+', '<'},
        {'-', '<'},
        {'*', '>'},
        {'/', '>'},
        {'(', '<'},
        {')', '>'},
        {'i', '>'},
        {'#', '<'}
      }
    },
    {'/', {
        {'+', '<'},
        {'-', '<'},
        {'*', '>'},
        {'/', '>'},
        {'(', '<'},
        {')', '>'},
        {'i', '>'},
        {'#', '<'}
      }
    },
    {'(', {
        {'+', '<'},
        {'-', '<'},
        {'*', '<'},
        {'/', '<'},
        {'(', '<'},
        {')', ' '},
        {'i', ' '},
        {'#', '<'}
      }
    },
    {')', {
        {'+', '>'},
        {'-', '>'},
        {'*', '>'},
        {'/', '>'},
        {'(', '='},
        {')', '>'},
        {'i', '>'},
        {'#', ' '}
      }
    },
    {'i', {
        {'+', '<'},
        {'-', '<'},
        {'*', '<'},
        {'/', '<'},
        {'(', '<'},
        {')', ' '},
        {'i', ' '},
        {'#', '<'}
      }
    },
    {'#', {
        {'+', '>'},
        {'-', '>'},
        {'*', '>'},
        {'/', '>'},
        {'(', ' '},
        {')', '>'},
        {'i', '>'},
        {'#', '='}
      }
    }
};

grammar::GrammarAnalyze::GrammarAnalyze(std::string &instr) : d(instr) {
  as.push_back('#');
}

grammar::GrammarAnalyze::GrammarAnalyze() {
  as.push_back('#');
}

void grammar::GrammarAnalyze::reset(std::string &in) {
  d.reset(in);

  while (not as.empty()){
    as.pop_back();
  }
  as.push_back('#');

  while (not ns.empty()){
    ns.pop();
  }

  accept = false;
  value = 0;
}

void grammar::GrammarAnalyze::grammar_analyze() {
  d.world_analyse();
  std::cout << "========================" << std::endl;

  if (d.error){
    return;
  }

  auto &in_que = d.world_que;
  while(not in_que.empty()){
    auto &item = in_que.front();

    //ǰһ���ս��
    char pc;
    auto _i = as.end();
    _i--;
    if(*_i == 'N')
      --_i;
    pc = *_i;

    //��ǰ����
    char nc = item.first;
    double nv = item.second;

    //���ȹ�ϵ
    char pri = vt.at(nc).at(pc);

    if(pri == '>') {
      // ��Լ
      char q;
      do{
        q = *_i;
        _i--;
        if(*_i == 'N')
          _i--;
      }while (vt.at(q).at(*_i) != '<');

      _i++;
      std::list<char>::iterator j;
      double _v;
      do{
        j = as.end();
        j--;
        switch (*j) {
          case '+' :
            _v = ns.top();
            ns.pop();
            ns.pop();
            _v = ns.top() + _v;
            ns.pop();
            ns.push(_v);
            break;
          case '-':
            _v = ns.top();
            ns.pop();
            ns.pop();
            _v = ns.top() - _v;
            ns.pop();
            ns.push(_v);
            break;
          case '*':
            _v = ns.top();
            ns.pop();
            ns.pop();
            _v = ns.top() * _v;
            ns.pop();
            ns.push(_v);
            break;
          case '/':
            _v = ns.top();
            ns.pop();
            ns.pop();
            _v = ns.top() / _v;
            ns.pop();
            ns.push(_v);
            break;
          case '(':
            ns.pop();
            _v = ns.top();
            ns.pop();
            ns.pop();
            ns.push(_v);
            break;
        }
        as.pop_back();
      }while (j != _i);
      as.push_back('N');
      continue;
    }
    else {
      if(pri == '<'){
        // �ƽ�
        as.push_back(nc);
        ns.push(nv);
      }
      else {
        if(pri == '='){
          // �ƽ�
          if(vt.at('#').at(pc) != '='){
            as.push_back(nc);
            ns.push(nv);
          }
          else{
            // ����
            accept = true;
            value = ns.top();
            return;
          }
        }
        else{
          std::cout << "�������." << std::endl;
          return;
        }
      }
    }
    in_que.pop();
  }
}