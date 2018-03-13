/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#include "catch.hpp"

#include "iostream.h"
#include "preprocessor.h"
#include "token.h"

#include <sstream>
#include <string>
#include <unordered_map>

using namespace dragon;

TEST_CASE("trigraph sequences are replaced (§5.2.1.1)", "[preprocessor]")
{
  // Escape trigraphs here to prevent replacement during compilation.
  std::unordered_map<std::string, std::string> trigraphs{
    { "\?\?=", "#" },  { "\?\?)", "]" }, { "\?\?!", "|" },
    { "\?\?(", "[" },  { "\?\?'", "^" }, { "\?\?>", "}" },
    { "\?\?/", "\\" }, { "\?\?<", "{" }, { "\?\?-", "~" },
  };

  for (auto it : trigraphs) {
    std::stringstream ss(it.first);
    IOStream ios(ss);
    auto token = PreProcessor(ios).getToken();
    REQUIRE(token.value == it.second);
  }
}

TEST_CASE("non-trigraph sequences are not replaced (§5.2.1.1)",
          "[preprocessor]")
{
  std::stringstream ss("???");
  IOStream ios(ss);
  PreProcessor pp(ios);

  REQUIRE(pp.getToken().value == "?");
  REQUIRE(pp.getToken().value == "?");
  REQUIRE(pp.getToken().value == "?");
}

TEST_CASE("backslash immediately followed by new-line is deleted (§5.1.1.2)",
          "[preprocessor]")
{
  std::stringstream ss("foo\\\nbar");
  IOStream ios(ss);
  PreProcessor pp(ios);

  REQUIRE(pp.getToken().value == "foobar");
}
