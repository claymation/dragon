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
