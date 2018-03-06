/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "iostream.h"
#include "preprocessor.h"

#include <sstream>
#include <string>
#include <unordered_map>

using namespace dragon;

TEST_CASE("trigraph sequences are replaced (§5.2.1.1)", "[preprocessor]")
{
  // Escape trigraphs here to prevent replacement during compilation.
  std::unordered_map<std::string, char> trigraphs{
    { "\?\?=", '#' },  { "\?\?)", ']' }, { "\?\?!", '|' },
    { "\?\?(", '[' },  { "\?\?'", '^' }, { "\?\?>", '}' },
    { "\?\?/", '\\' }, { "\?\?<", '{' }, { "\?\?-", '~' },
  };

  for (auto it : trigraphs) {
    std::stringstream ss(it.first);
    IOStream ios(ss);

    REQUIRE(PreProcessor(ios).getToken() == it.second);
  }
}

TEST_CASE("non-trigraph sequences are not replaced (§5.2.1.1)",
          "[preprocessor]")
{
  std::stringstream ss("???");
  IOStream ios(ss);
  PreProcessor pp(ios);

  REQUIRE(pp.getToken() == '?');
  REQUIRE(pp.getToken() == '?');
  REQUIRE(pp.getToken() == '?');
}
