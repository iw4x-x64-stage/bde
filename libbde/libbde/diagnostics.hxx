// Copyright (c) the IW4x authors (see the AUTHORS file).
// SPDX-License-Identifier: GPL-3.0-only WITH AdditionRef-IW4x-Exception-1.1

#pragma once

#include <quill/Logger.h>
#include <quill/LogMacros.h>
#include <quill/bundled/fmt/format.h> // formatter of format_as()

#include <libbde/types.hxx>
#include <libbde/utility.hxx>

#include <libbde/export.hxx>

namespace bde
{
  // The diagnostics are written to stderr by the quill backend thread, one
  // line per record and in the build2 shape: the message carries its own
  // prefix (`<endpoint>: warning: ...`, `error: ...`) and nothing else is
  // added. The record's level decides whether it is written, according to
  // the verbosity (see set_verbosity()):
  //
  // LOG_ERROR     errors (any verbosity)
  // LOG_WARNING   warnings (1 and above)
  // LOG_NOTICE    high-level information, such as connected users (1)
  // LOG_INFO      essential progress, such as the listening address (2)
  // LOG_DEBUG     all progress (3)
  // LOG_TRACE_L1  information helpful to the user (4)
  // LOG_TRACE_L2  information helpful to the developer (5)
  // LOG_TRACE_L3  even more detail (6)
  //
  // Note that the records are queued and written asynchronously, with the
  // queue drained when the process exits normally.

  // Return the diagnostics logger, starting the backend and creating the
  // logger on the first call. The initial verbosity is 1.
  //
  LIBBDE_SYMEXPORT quill::Logger*
  logger ();

  // Set the verbosity, on the build2 scale from 0 (errors only) to 6.
  //
  LIBBDE_SYMEXPORT void
  set_verbosity (uint16_t);

  // Format the named enumerations as their names in the records. Quill
  // formats the records with its bundled fmt, which finds this function by
  // argument-dependent lookup.
  //
  template <named_enum T>
  inline const char*
  format_as (T v) {return to_string (v);}
}
