/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "catch.hpp"

#include "iostream.h"
#include "lexicalanalyzer.h"
#include "token.h"

#include <sstream>
#include <string>
#include <vector>

using namespace dragon;

TEST_CASE("newlines are preserved", "[lexicalanalyzer]")
{
  std::stringstream ss("\n");
  IOStream ios(ss);
  LexicalAnalyzer lex(ios);

  REQUIRE(lex.getToken().kind == PPToken::Kind::NewLine);
}

TEST_CASE("tokenize identifiers (§6.4.2.1)", "[lexicalanalyzer]")
{
  std::stringstream ss("foo_bar_42");
  IOStream ios(ss);
  LexicalAnalyzer lex(ios);
  PPToken token = lex.getToken();

  REQUIRE(token.kind == PPToken::Kind::Identifier);
  REQUIRE(token.value == "foo_bar_42");
}

TEST_CASE("tokenize preprocessing numbers (§6.4.8)", "[lexicalanalyzer]")
{
  std::stringstream ss("6.02E23");
  IOStream ios(ss);
  LexicalAnalyzer lex(ios);
  PPToken token = lex.getToken();

  REQUIRE(token.kind == PPToken::Kind::PPNumber);
  REQUIRE(token.value == "6.02E23");
}

TEST_CASE("tokenize punctuators (§6.4.6)", "[lexicalanalyzer]")
{
  std::stringstream ss;
  std::vector<std::string> punc{
    "[",  "]",  "(",  ")",  "{",   "}",   ".",  "->", "++", "--",  "&",  "*",
    "+",  "-",  "~",  "!",  "/",   "%",   "<<", ">>", "<",  ">",   "<=", ">=",
    "==", "!=", "^",  "|",  "&&",  "||",  "?",  ":",  ";",  "...", "=",  "*=",
    "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=", "#",   ",",  "##",
  };

  for (auto s : punc) {
    ss << s;
  }

  IOStream ios(ss);
  LexicalAnalyzer lex(ios);

  for (auto s : punc) {
    PPToken token = lex.getToken();

    REQUIRE(token.kind == PPToken::Kind::Punctuator);
    REQUIRE(token.value == s);
  }
}

TEST_CASE("tokenize character constants (§6.4.4.4)", "[lexicalanalyzer]")
{
  std::stringstream ss("'a'");
  IOStream ios(ss);
  LexicalAnalyzer lex(ios);
  PPToken token = lex.getToken();

  REQUIRE(token.kind == PPToken::Kind::CharacterConstant);
  REQUIRE(token.value == "a");
}

TEST_CASE("tokenize string literals (§6.4.5)", "[lexicalanalyzer]")
{
  std::stringstream ss("\"foo\"");
  IOStream ios(ss);
  LexicalAnalyzer lex(ios);
  PPToken token = lex.getToken();

  REQUIRE(token.kind == PPToken::Kind::StringLiteral);
  REQUIRE(token.value == "foo");
}
