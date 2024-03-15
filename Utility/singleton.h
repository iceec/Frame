#pragma once

#include <iostream>

#define SINGLE(a)        \
  friend single<a>;      \
                         \
private:                 \
  a();                   \
  a(const a &) = delete; \
  ~a();                  \
  a &operator=(const a &) = delete;

// 包含+define
template <class T>
class single
{
public:
  static T *instance()
  {
    static T a;
    return &a;
  }
};


