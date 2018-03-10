/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "catch.hpp"

#include "iostream.h"
#include "lexicalanalyzer.h"
#include "token.h"

#include <sstream>

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
