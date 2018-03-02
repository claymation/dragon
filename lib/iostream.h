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
