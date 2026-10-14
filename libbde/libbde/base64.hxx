// Copyright (c) the IW4x authors (see the AUTHORS file).
// SPDX-License-Identifier: GPL-3.0-only WITH AdditionRef-IW4x-Exception-1.1

#pragma once

#include <libbde/types.hxx>
#include <libbde/utility.hxx>

#include <libbde/export.hxx>

namespace bde
{
  // Base64-encode the data using the standard alphabet with padding and
  // without line breaks (the form Demonware JSON messages use).
  //
  LIBBDE_SYMEXPORT string
  base64_encode (span<const uint8_t>);

  // Base64-decode a string in the above form. Throw invalid_argument if it
  // is not a valid representation.
  //
  LIBBDE_SYMEXPORT bytes
  base64_decode (string_view);

  // Base64-encode the data using the URL and filename safe alphabet without
  // padding (the form JSON Web Signatures use; see RFC 7515).
  //
  LIBBDE_SYMEXPORT string
  base64url_encode (span<const uint8_t>);

  // Base64-decode a string in the above form. Throw invalid_argument if it
  // is not a valid representation.
  //
  LIBBDE_SYMEXPORT bytes
  base64url_decode (string_view);
}
