/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "lexicalanalyzer.h"

#include <cassert>

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
    case '.':
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
LexicalAnalyzer::getPPNumber(int c)
{
  PPToken token{ PPToken::Kind::PPNumber, "" };

  while (true) {
    token.value += static_cast<char>(c);
    c = source.get();
    switch (c) {
      case '+':
      case '-': {
        int back = std::tolower(token.value.back());
        if (!(back == 'e' || back == 'p')) {
          source.putback(c);
          return token;
        }
        break;
      }

      default:
        if (!(std::isalnum(c) || c == '.' || c == '_')) {
          source.putback(c);
          return token;
        }
        break;
    }
  }
}

PPToken
LexicalAnalyzer::getCharacterConstant()
{
  PPToken token{ PPToken::Kind::CharacterConstant, "" };

  while (true) {
    int c = source.get();

    if (c == '\n' || c == EOF) {
      return { PPToken::Kind::Invalid, "" };
    }

    if (c == '\'') {
      break;
    }

    token.value += static_cast<char>(c);
  }

  return token;
}

PPToken
LexicalAnalyzer::getStringLiteral()
{
  return { PPToken::Kind::StringLiteral, "" };
}

PPToken
LexicalAnalyzer::getPunctuator(int c)
{
  PPToken token{ PPToken::Kind::Punctuator, "" };

  token.value += static_cast<char>(c);

  switch (c) {
    case '[':
    case ']':
    case '(':
    case ')':
    case '{':
    case '}':
    case '~':
    case '?':
    case ':':
    case ';':
    case ',':
      // simple punctuators
      return token;

    default:
      break;
  }

  int next = source.get();

  switch (c) {
    case '.':
      if (std::isdigit(next)) {
        source.putback(next);
        return getPPNumber('.');
      }
      if (next != '.') {
        source.putback(next);
        break;
      }
      next = source.get();
      if (next != '.') {
        source.putback(next);
        source.putback('.');
        break;
      }
      token.value = "...";
      break;

    case '-':
      if (next == '>') {
        token.value += static_cast<char>(next);
        break;
      }
      if (next == c || next == '=') {
        token.value += static_cast<char>(next);
      } else {
        source.putback(next);
      }
      break;

    case '+':
    case '&':
    case '|':
      if (next == c || next == '=') {
        token.value += static_cast<char>(next);
      } else {
        source.putback(next);
      }
      break;

    case '*':
    case '!':
    case '/':
    case '%':
    case '=':
    case '^':
      if (next == '=') {
        token.value += static_cast<char>(next);
      } else {
        source.putback(next);
      }
      break;

    case '<':
    case '>':
      if (next == c) {
        token.value += static_cast<char>(next);
        next = source.get();
      }
      if (next == '=') {
        token.value += static_cast<char>(next);
      } else {
        source.putback(next);
      }
      break;

    case '#':
      if (next == c) {
        token.value += static_cast<char>(next);
      } else {
        source.putback(next);
      }
      break;

    default:
      // can't happen
      assert(false);
  }

  return token;
}

} // namespace dragon
