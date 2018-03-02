#include "preprocessor.h"

namespace dragon {

PreProcessor::PreProcessor(Stream& source)
  : trigraph_filter(source)
  , source(trigraph_filter)
{}

int
PreProcessor::getToken()
{
  return source.get();
}

PreProcessor::TrigraphFilter::TrigraphFilter(Stream& source)
  : StreamFilter(source)
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