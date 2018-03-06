/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_iostream_h
#define dragon_iostream_h

#include "stream.h"

#include <iostream>

namespace dragon {

class IOStream : public Stream
{
public:
  explicit IOStream(std::iostream& ios)
    : ios(ios)
  {}

  int get() override { return ios.get(); }

  void putback(char c) override { ios.putback(c); }

private:
  std::iostream& ios;
};

} // namespace dragon

#endif
