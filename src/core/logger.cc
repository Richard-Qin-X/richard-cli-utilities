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

#include "rcli/core/logger.h"

#include <iostream>
#include <string_view>

namespace rcli::core {
constexpr std::string_view kColorReset = "\033[0m";
constexpr std::string_view kColorRed = "\033[31m";
constexpr std::string_view kColorGreen = "\033[32m";
constexpr std::string_view kColorYellow = "\033[33m";
constexpr std::string_view kColorCyan = "\033[36m";
constexpr std::string_view kStyleBold = "\033[1m";

void log_info(std::string_view message) {
  std::cout << kStyleBold << kColorCyan << "[ INFO ] " << kColorReset << message
            << "\n";
}
void log_success(std::string_view message) {
  std::cout << kStyleBold << kColorGreen << "[  OK  ] " << kColorReset
            << message << "\n";
}

void log_warning(std::string_view message) {
  std::cout << kStyleBold << kColorYellow << "[ WARN ] " << kColorReset
            << message << "\n";
}

void log_error(std::string_view message) {
  std::cerr << kStyleBold << kColorRed << "[ FAIL ] " << kColorReset << message
            << "\n";
}
}  // namespace rcli::core
