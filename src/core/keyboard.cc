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

#include "rcli/core/keyboard.h"

#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

struct termios g_orig_termios {
};  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
namespace rcli::core {

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &g_orig_termios);
  struct termios raw = g_orig_termios;
  raw.c_lflag &= static_cast<tcflag_t>(
      ~(static_cast<unsigned int>(ECHO) | static_cast<unsigned int>(ICANON)));
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios); }

bool kbhit() {
  struct timeval timeout = {0L, 0L};  // NOLINT(misc-include-cleaner)
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &timeout) > 0;
}

char get_key() {
  char ch{};
  if (read(STDIN_FILENO, &ch, 1) == 1) {
    return ch;
  }
  return '\0';
}
}  // namespace rcli::core