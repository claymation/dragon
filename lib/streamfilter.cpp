/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "streamfilter.h"

namespace dragon {

StreamFilter::StreamFilter(Stream& in)
  : source(in)
{}

int
StreamFilter::get()
{
  if (!buffer.empty()) {
    int c = buffer.back();
    buffer.pop_back();
    return c;
  }

  return filter();
}

void
StreamFilter::putback(int c)
{
  buffer.push_back(c);
}

} // namespace dragon
