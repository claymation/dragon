#ifndef dragon_streamfilter_h
#define dragon_streamfilter_h

#include "stream.h"

#include <string>

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
  void putback(char) override;

protected:
  /**
   * @ brief Get a filtered character from the underlying stream.
   */
  virtual int filter() = 0;

  Stream& source;

private:
  std::string buffer;
};

} // namespace dragon

#endif
