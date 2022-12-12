#ifndef MINPASS_SRC_CONFIGURATION_CONFIG_H_
#define MINPASS_SRC_CONFIGURATION_CONFIG_H_

// This is a configuration file which will be used to generate config.h file

#include <string_view>

namespace minpass::config {
inline constexpr std::string_view project_name = "minpass";
inline constexpr std::string_view project_version = "v0.0.1";
inline constexpr int project_version_major{0};
inline constexpr int project_version_minor{0};
inline constexpr int project_version_patch{1};
inline constexpr std::string_view git_sha = "315635114dd12bbb5ff91fa4324b16d801ec3047";
}  // namespace minpass::config

#endif  // MINPASS_SRC_CONFIGURATION_CONFIG_H_
