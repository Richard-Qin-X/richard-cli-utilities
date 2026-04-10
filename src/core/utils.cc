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

#include "rcli/core/utils.h"

#include <iomanip>
#include <iostream>
#include <string_view>

#include "rcli/core/terminal.h"

namespace rcli::core {
int get_center_padding(int content_width) {
  const int term_width = get_terminal_width();
  if (content_width >= term_width) {
    return 0;
  }
  return (term_width - content_width) / 2;
}

void print_centered(std::string_view text) {
  const int padding = get_center_padding(static_cast<int>(text.length()));
  if (padding > 0) {
    std::cout << std::setw(padding) << "" << text << "\n";
  } else {
    std::cout << text << "\n";
  }
}
}  // namespace rcli::core