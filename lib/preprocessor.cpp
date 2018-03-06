/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "preprocessor.h"

namespace dragon {

PreProcessor::PreProcessor(Stream& in)
  : trigraph_filter(in)
  , source(trigraph_filter)
{}

int
PreProcessor::getToken()
{
  return source.get();
}

PreProcessor::TrigraphFilter::TrigraphFilter(Stream& in)
  : StreamFilter(in)
{}

int
PreProcessor::TrigraphFilter::filter()
{
  int c = source.get();
  if (c != '?') {
    return c;
  }

  c = source.get();
  if (c != '?') {
    source.putback(c);
    return '?';
  }

  c = source.get();
  switch (c) {
    case '=':
      return '#';
    case '(':
      return '[';
    case ')':
      return ']';
    case '<':
      return '{';
    case '>':
      return '}';
    case '!':
      return '|';
    case '\'':
      return '^';
    case '/':
      return '\\';
    case '-':
      return '~';
    default:
      source.putback(c);
      source.putback('?');
      return '?';
  }
}

} // namespace dragon
