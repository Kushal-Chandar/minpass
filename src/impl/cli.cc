#include "cli.h"

#include <fmt/core.h>

#include <CLI/CLI.hpp>
#include <optional>

#include "config.h"

namespace minpass {

auto CLI::Parse(int argc, char const **argv) noexcept -> std::optional<int> {
  ::CLI::App minpass_cli{"Minpass is a self-hosted password manager."};

  // Add flags and options here
  bool version = false;
  minpass_cli.add_flag("-v,--version", version, "Show version information");

  try {
    minpass_cli.parse(argc, argv);
  } catch (const ::CLI::ParseError &parse_error) {
    return minpass_cli.exit(parse_error);
  }

  // Implement funtionality based on flags and options
  if (version) {
    fmt::print("{} version {}\n\ncommit: {}\n", minpass::config::project_name,
               minpass::config::project_version, minpass::config::git_sha);
    return EXIT_SUCCESS;
  }

  return std::nullopt;
}

}  // namespace minpass
