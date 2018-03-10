/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "lexicalanalyzer.h"

namespace dragon {

LexicalAnalyzer::LexicalAnalyzer(Stream& in)
  : source(in)
{}

PPToken
LexicalAnalyzer::getToken()
{
  int c = source.get();
  switch (c) {
    case '_':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
      return getIdentifier(c);

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return getPPNumber(c);

    case '.':
      c = source.get();
      if (std::isdigit(c)) {
        source.putback(c);
        return getPPNumber('.');
      }
      return getPunctuator('.');

    case '\'':
      return getCharacterConstant();

    case '"':
      return getStringLiteral();

    case '[':
    case ']':
    case '(':
    case ')':
    case '{':
    case '}':
    case '-':
    case '+':
    case '&':
    case '*':
    case '~':
    case '!':
    case '/':
    case '%':
    case '<':
    case '>':
    case '=':
    case '^':
    case '|':
    case '?':
    case ':':
    case ';':
    case ',':
    case '#':
      return getPunctuator(c);

    case '\n':
      return { PPToken::Kind::NewLine, "" };

    case EOF:
      return { PPToken::Kind::End, "" };

    default:
      return { PPToken::Kind::Invalid, "" };
  }
}

PPToken
LexicalAnalyzer::getIdentifier(int c)
{
  PPToken token { PPToken::Kind::Identifier, "" };

  while (true) {
    token.value += static_cast<char>(c);
    c = source.get();
    if (!(std::isalnum(c) || c == '_')) {
      source.putback(c);
      return token;
    }
  }
}

PPToken
LexicalAnalyzer::getPPNumber(int)
{
  return { PPToken::Kind::PPNumber, "" };
}

PPToken
LexicalAnalyzer::getCharacterConstant()
{
  return { PPToken::Kind::CharacterConstant, "" };
}

PPToken
LexicalAnalyzer::getStringLiteral()
{
  return { PPToken::Kind::StringLiteral, "" };
}

PPToken
LexicalAnalyzer::getPunctuator(int)
{
  return { PPToken::Kind::Punctuator, "" };
}

} // namespace dragon
