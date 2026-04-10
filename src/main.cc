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
 * GNU General Public    License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <unistd.h>  // POSIX execvp

#include <cstddef>
#include <array>
#include <climits>
#include <cstring>
#include <libgen.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <vector>

void print_help() {
  std::cout << "rcli - Richard CLI Utilities\n\n"
            << "Usage: rcli <command> [args...]\n\n"
            << "  Copyright (C) 2026  Richard Qin\n"
            << "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
            << "This is free software, and you are welcome to redistribute it\n"
            << "under certain conditions; type `show c' for details.\n\n";
}

// GPL Warranty

void print_warranty() {
  std::cout
      << "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
      << "APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE "
         "COPYRIGHT\n"
      << "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT "
         "WARRANTY\n"
      << "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED "
         "TO,\n"
      << "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A "
         "PARTICULAR\n"
      << "PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE "
         "PROGRAM\n"
      << "IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE "
         "COST OF\n"
      << "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n";
}

// GPL Conditions

void print_conditions() {
  std::cout
      << "This program is free software: you can redistribute it and/or "
         "modify\n"
      << "it under the terms of the GNU General Public License as published "
         "by\n"
      << "the Free Software Foundation, either version 3 of the License, or\n"
      << "(at your option) any later version.\n\n"
      << "This program is distributed in the hope that it will be useful,\n"
      << "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
      << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
      << "GNU General Public License for more details.\n\n"
      << "You should have received a copy of the GNU General Public License\n"
      << "along with this program.  If not, see "
         "<https://www.gnu.org/licenses/>.\n";
}

int main(int argc, char** argv) {
  const std::span<char*> args(argv, static_cast<size_t>(argc));

  if (args.size() < 2) {
    std::cerr << "Usage: rcli <command> [args...]\n";
    return 1;
  }

  const std::string command(args[1], std::allocator<char>());

  if (command == "help" || command == "--help" || command == "-h") {
    print_help();
    return 0;
  }

  if (command == "show" && argc >= 3) {
    const std::string sub_command(argv[2], std::allocator<char>());
    if (sub_command == "w") {
      print_warranty();
      return 0;
    }
    if (sub_command == "c") {
      print_conditions();
      return 0;
    }
    
    {
      std::cerr << "rcli error: Unknown show option '" << sub_command
                << "'. Use 'w' or 'c'.\n";
      return 1;
    }
  }


  std::array<char, PATH_MAX> path_buffer{};
  const ssize_t count = readlink("/proc/self/exe", path_buffer.data(), PATH_MAX - 1);
  if (count == -1) {
    std::perror("rcli error: Failed to locate self");
    return 1;
  }
    if (count >= 0 && static_cast<size_t>(count) < path_buffer.size()) {
      path_buffer.at(static_cast<size_t>(count)) = '\0';
    }

  const std::string exe_path(path_buffer.data());
  std::array<char, PATH_MAX> exe_path_copy{};
  std::strncpy(exe_path_copy.data(), exe_path.c_str(), PATH_MAX);
  char* dir_path = dirname(exe_path_copy.data());

  const std::string target_binary = std::string(dir_path) + "/rcli-" + command;

  std::vector<char*> exec_args;
  exec_args.push_back(const_cast<char*>(target_binary.c_str())); // NOLINT(cppcoreguidelines-pro-type-const-cast)
  for (size_t i = 2; i < static_cast<size_t>(argc); ++i) {
    exec_args.push_back(args[i]);
  }
  exec_args.push_back(nullptr);

  execvp(target_binary.c_str(), exec_args.data());

  perror("rcli error: Failed to execute command");
  return 1;
}