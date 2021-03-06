/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "iostream.h"

namespace dragon {

IOStream::~IOStream() = default;

void
IOStream::putback(int c)
{
  ios.clear();
  if (c >= 0) {
    ios.putback(static_cast<char>(c));
  }
}

} // namespace dragon
