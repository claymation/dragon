/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_stream_h
#define dragon_stream_h

namespace dragon {

class Stream
{
public:
  /**
   * @brief Get a character from the stream, or EOF.
   */
  virtual int get() = 0;

  /**
   * @brief Put a character back into the stream.
   */
  virtual void putback(char) = 0;
};

} // namespace dragon

#endif
