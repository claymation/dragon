/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_preprocessor_h
#define dragon_preprocessor_h

#include "stream.h"
#include "streamfilter.h"

namespace dragon {

/**
 * @brief The preprocessor prepares source text for translation.
 *
 * The parser pulls tokens from the preprocessor, which
 * pulls preprocessor tokens from the lexical analyzer,
 * which in turn pulls characters from the source stream
 * (through various text-processing filters):
 *
 *   Parser::parse()
 *     PreProcessor::getToken()
 *       PreProcessor::concatenateStringLiterals()
 *         PreProcessor::expandEscapeSequences()
 *           PreProcessor::execute()
 *             LexicalAnalyzer::getToken()
 *               PreProcessor::ContinuedLineFilter::get()
 *                 PreProcessor::TrigraphFilter::get()
 *                   IOStream::get()
 */
class PreProcessor
{
public:
  explicit PreProcessor(Stream&);

  /**
   * @brief Get the next parser token from the source stream.
   */
  int getToken();

private:
  class TrigraphFilter : public StreamFilter
  {
  public:
    TrigraphFilter(Stream&);

    int filter() override;
  };

  TrigraphFilter trigraph_filter;
  Stream& source;
};

} // namespace dragon

#endif
