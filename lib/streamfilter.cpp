#include "streamfilter.h"

namespace dragon {

StreamFilter::StreamFilter(Stream& source)
  : source(source)
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
StreamFilter::putback(char c)
{
  buffer.push_back(c);
}

} // namespace dragon
