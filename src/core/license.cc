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

#include "rcli/core/license.h"

#include <unistd.h>

#include <iostream>
#include <string>

namespace rcli::core {
void init_interactive_module(const std::string& module_name) {
  if (isatty(STDOUT_FILENO) != 0) {
    std::cout
        << module_name << "  Copyright (C) 2026  Richard Qin\n"
        << "This program comes with ABSOLUTELY NO WARRANTY; for details type "
           "`rcli show w'.\n"
        << "This is free software, and you are welcome to redistribute it\n"
        << "under certain conditions; type `rcli show c' for details.\n\n";

    std::cout << "Press [Enter] to start..." << std::flush;
    std::cin.get();
  }
}
}  // namespace rcli::core
