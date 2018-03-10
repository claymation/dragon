/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_lexicalanalyzer_h
#define dragon_lexicalanalyzer_h

#include "stream.h"
#include "token.h"

namespace dragon {

class LexicalAnalyzer
{
public:
  explicit LexicalAnalyzer(Stream&);

  PPToken getToken();

private:
  PPToken getIdentifier(int);
  PPToken getPPNumber(int);
  PPToken getCharacterConstant();
  PPToken getStringLiteral();
  PPToken getPunctuator(int);

  Stream& source;
};

} // namespace dragon

#endif
