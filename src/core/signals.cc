/*
 * Richard CLI Utilities - A collection of modular command-line utilities.
 * Copyright (C) 2026  Richard Qin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "rcli/core/signals.h"

#include <atomic>
#include <csignal>
#include <cstdlib>

#include "rcli/core/terminal.h"

namespace rcli::core {

void handle_signal(int signal) {
  if (signal == SIGINT || signal == SIGTERM) {
    g_keep_running = false;
  }
}

void setup_signal_handlers() {
  static_cast<void> (std::signal(SIGINT, handle_signal));
  static_cast<void> (std::signal(SIGTERM, handle_signal));

  static_cast<void> (std::atexit([]() { show_cursor(); }));
}
}  // namespace rcli::core