// Copyright (c) the IW4x authors (see the AUTHORS file).
// SPDX-License-Identifier: GPL-3.0-only WITH AdditionRef-IW4x-Exception-1.1

#include <libbde/diagnostics.hxx>

#include <chrono>

#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/sinks/ConsoleSink.h>

using namespace std;

namespace bde
{
  quill::Logger*
  logger ()
  {
    static quill::Logger* const r ([] ()
    {
      // The backend polls the queues and sleeps between the polls when they
      // are empty. A server logs rarely, so we let it sleep for a few
      // milliseconds, which keeps an idle server off the processor.
      //
      quill::BackendOptions bo;
      bo.thread_name = "diagnostics";
      bo.sleep_duration = chrono::milliseconds (5);

      quill::Backend::start (bo);

      // The message carries the whole line (see the header), so the pattern
      // is the message alone and the output is plain text.
      //
      quill::ConsoleSinkConfig sc;
      sc.set_stream ("stderr");
      sc.set_colour_mode (quill::ConsoleSinkConfig::ColourMode::Never);

      quill::Logger* l (
        quill::Frontend::create_or_get_logger (
          "bde",
          quill::Frontend::create_or_get_sink<quill::ConsoleSink> ("stderr",
                                                                   sc),
          quill::PatternFormatterOptions ("%(message)")));

      l->set_log_level (quill::LogLevel::Notice);
      return l;
    } ());

    return r;
  }

  void
  set_verbosity (uint16_t v)
  {
    LIBBDE_PRE (v <= 6);

    static const quill::LogLevel levels[]
    {
      quill::LogLevel::Error,
      quill::LogLevel::Notice,
      quill::LogLevel::Info,
      quill::LogLevel::Debug,
      quill::LogLevel::TraceL1,
      quill::LogLevel::TraceL2,
      quill::LogLevel::TraceL3
    };

    logger ()->set_log_level (levels[v]);
  }
}
