// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char ch) {
  switch (ch) {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
      return 2;
    case '-':
      return 2;
    case '*':
      return 3;
    case '/':
      return 3;
  }
  return -1;
}

bool isDigit(std::string pref) {
  for (size_t i = 0; i < pref.size(); ++i) {
    if (pref[i] < '0' || pref[i] > '9')
      return false;
  }
  return true;
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 100> itstack;
  std::string res;
  for (size_t i = 0; i < inf.size(); i++) {
    if ((priority(inf[i]) == -1) && (priority(inf[i]) != 1)) {
      if (!res.empty() && priority(inf[i - 1]) != -1) {
        res.push_back(' ');
      }
      res.push_back(inf[i]);
    } else if ((priority(inf[i]) > priority(itstack.get())) || (itstack.isEmpty()) || (priority(inf[i]) == 0)) {
      itstack.push(inf[i]);
    } else {
      if (priority(inf[i]) == 1) {
        while (priority(itstack.get()) != 0) {
          res.push_back(' ');
          res.push_back(itstack.get());
          itstack.pop();
        }
        itstack.pop();
      } else {
        while (priority(itstack.get()) >= priority(inf[i])) {
          res.push_back(' ');
          res.push_back(itstack.get());
          itstack.pop();
        }
        itstack.push(inf[i]);
      }
    }
  }
  while (!itstack.isEmpty()) {
    res.push_back(' ');
    if (priority(itstack.get()) != 0) {
      res.push_back(itstack.get());
    }
    itstack.pop();
  }
  return res;
}

int eval(std::string post) {
  TStack <int, 100> ptstack;
  std::string temp;
  int oper1 = 0;
  int oper2 = 0;
  size_t start = 0, end = 0;
  for (size_t i = 0; i < post.size(); ++i) {
    if (post[i] == ' ' || i == post.size()-1) {
      end = i;
      if (i == post.size() - 1)
        end++;
      temp = post.substr(start, end - start);
      start = end + 1;
      if (isDigit(temp)) {
        ptstack.push(std::stoi(temp));
      } else {
        oper2 = ptstack.get();
        ptstack.pop();
        oper1 = ptstack.get();
        ptstack.pop();
        if (temp == "+")
          ptstack.push(oper1 + oper2);
        else if (temp == "-")
          ptstack.push(oper1 - oper2);
        else if (temp == "*")
          ptstack.push(oper1 * oper2);
        else if (temp == "/")
          ptstack.push(oper1 / oper2);
      }
    }
  }
  return ptstack.get();
}
