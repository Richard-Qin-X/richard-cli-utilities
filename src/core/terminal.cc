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

#include "rcli/core/terminal.h"

#include <sys/ioctl.h>  // ioctl, TIOCGWINSZ
#include <unistd.h>     // STDOUT_FILENO

#include <iostream>

namespace rcli::core {

constexpr int kDefaultWidth = 80;
constexpr int kDefaultHeight = 24;

void hide_cursor() { std::cout << "\033[?25l" << std::flush; }

void show_cursor() { std::cout << "\033[?25h" << std::flush; }

void clear_screen() { std::cout << "\033[2J\033[H" << std::flush; }

int get_terminal_width() {
  struct winsize window_size{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1) { // NOLINT(misc-include-cleaner)
    return kDefaultWidth;
  }
  return window_size.ws_col;
}

int get_terminal_height() {
  struct winsize window_size{};
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1) {
    return kDefaultHeight;
  }
  return window_size.ws_row;
}
}  // namespace rcli::core