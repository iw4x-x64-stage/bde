// Copyright (c) the IW4x authors (see the AUTHORS file).
// SPDX-License-Identifier: GPL-3.0-only WITH AdditionRef-IW4x-Exception-1.1

#include <string>
#include <cstdint>
#include <print>
#include <iostream>

#include <libobe/diagnostics.hxx>

#undef NDEBUG
#include <cassert>

using namespace std;
using namespace obe;

// Usage: argv[0] [<verbosity>]
//
// Set the verbosity, if specified, then read lines in the form:
//
// <level> <message>
//
// from stdin and log each message at the level, one of error, warning,
// notice, info, debug, trace-l1, trace-l2, and trace-l3.
//
int
main (int argc, char* argv[])
{
  if (argc > 2)
  {
    println (cerr, "error: unexpected argument '{}'", argv[2]);
    return 1;
  }

  if (argc == 2)
    set_verbosity (static_cast<uint16_t> (stoul (argv[1])));

  for (string l; getline (cin, l); )
  {
    const size_t p (l.find (' '));
    assert (p != string::npos);

    const string v (l, 0, p);
    const string m (l, p + 1);

    quill::Logger* const g (logger ());

    if      (v == "error")    LOG_ERROR    (g, "{}", m);
    else if (v == "warning")  LOG_WARNING  (g, "{}", m);
    else if (v == "notice")   LOG_NOTICE   (g, "{}", m);
    else if (v == "info")     LOG_INFO     (g, "{}", m);
    else if (v == "debug")    LOG_DEBUG    (g, "{}", m);
    else if (v == "trace-l1") LOG_TRACE_L1 (g, "{}", m);
    else if (v == "trace-l2") LOG_TRACE_L2 (g, "{}", m);
    else if (v == "trace-l3") LOG_TRACE_L3 (g, "{}", m);
    else
    {
      println (cerr, "error: unknown level '{}'", v);
      return 1;
    }
  }
}
