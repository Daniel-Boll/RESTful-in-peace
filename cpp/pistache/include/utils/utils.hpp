#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <fmt/core.h>
#include <pistache/http_defs.h>
#include <sstream>

namespace Utils {
namespace Routes {

std::string routeCompose(const std::string &prefix, const std::string &path);

std::pair<std::string, std::string>
pathComposedExtraction(std::string pathComposed);

static std::unordered_map<std::string, Pistache::Http::Method> mapMethods{
    {"get", Pistache::Http::Method::Get},
    {"post", Pistache::Http::Method::Post},
    {"put", Pistache::Http::Method::Put},
    {"delete", Pistache::Http::Method::Delete},
};

} // namespace Routes
} // namespace Utils
#endif // UTILS_HPP
