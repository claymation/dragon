/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_streamfilter_h
#define dragon_streamfilter_h

#include "stream.h"

#include <vector>

namespace dragon {

class StreamFilter : public Stream
{
public:
  explicit StreamFilter(Stream&);

  /**
   * @brief Get a character from the stream, or EOF.
   */
  int get() override;

  /**
   * @brief Put a character back into the stream.
   */
  void putback(int) override;

protected:
  /**
   * @ brief Get a filtered character from the underlying stream.
   */
  virtual int filter() = 0;

  Stream& source;

private:
  std::vector<int> buffer;
};

} // namespace dragon

#endif
