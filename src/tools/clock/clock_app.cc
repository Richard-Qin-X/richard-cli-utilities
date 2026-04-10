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

#include <atomic>
#include <chrono>
#include <csignal>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>

#include "rcli/core/license.h"
#include "rcli/core/terminal.h"

namespace {
std::atomic<bool> running{
    true};  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
}

void handle_sigint(int /* signal */) { running = false; }

namespace {
constexpr std::chrono::milliseconds kRefreshInterval{100};
}

int main() {
  rcli::core::init_interactive_module("rcli-clock");

  std::signal(SIGINT, handle_sigint);
  rcli::core::hide_cursor();

  while (running) {
    rcli::core::clear_screen();

    auto now = std::chrono::system_clock::now();
    const std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_time{};

    if (localtime_r(&time_t_now, &local_time) != nullptr) {
      std::cout << "\n\n  ";
      std::cout << std::setfill('0') << std::setw(2) << local_time.tm_hour
                << ":" << std::setfill('0') << std::setw(2) << local_time.tm_min
                << ":" << std::setfill('0') << std::setw(2) << local_time.tm_sec
                << "\n";

      std::cout << std::flush;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(kRefreshInterval));
  }

  rcli::core::clear_screen();
  rcli::core::show_cursor();

  return 0;
}