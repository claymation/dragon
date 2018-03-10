/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */

#ifndef dragon_token_h
#define dragon_token_h

#include <string>

namespace dragon {

struct PPToken
{
public:
  enum class Kind
  {
    Invalid,

    HeaderName,
    Identifier,
    PPNumber,
    CharacterConstant,
    StringLiteral,
    Punctuator,

    Space,
    NewLine,
    End,
  };

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
  Kind kind;
  std::string value;
#pragma clang diagnostic pop
};

} // namespace dragon

#endif
