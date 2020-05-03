#include <sys/mman.h>
#include <spdlog/spdlog.h>
#include <sys/utsname.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>


template<typename T>
inline std::string get_error(const T& msg) {
  char buffer[250];
  std::ostringstream out;
  out << msg << ": " << strerror_r(errno, buffer, sizeof(buffer));
  return out.str();
}

inline long string_to_long(const std::string& in) {
  char* txt_end;
  return std::strtol(in.c_str(), &txt_end, 10);
}

class KernelDetails {
private:
  utsname kernel_details {};
public:
  long kernel_major;
  long kernel_minor;
  long kernel_patch;
  std::string release;
  std::string os;

  KernelDetails() {
    const int res = uname(&kernel_details);
    if (res == -1) {
      throw std::runtime_error(get_error(
          "unable to retrieve kernel details"));
    }
    release = std::string(kernel_details.release);
    os = std::string(kernel_details.sysname);

    std::vector<std::string> results;
    boost::split(results, release, [](char c){return c == '.';});

    const auto size = results.size();
    if (size>0) {
      kernel_major = string_to_long(results[0]);
    }

    if (size>1) {
      kernel_minor = string_to_long(results[1]);
    }

    if (size>2) {
      kernel_patch = string_to_long(results[2]);
    }
  }
};


int main(int argc, char* argv[]) {
  spdlog::info("Booting up... (spdlog version {}.{}.{})",
               SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

  spdlog::info("Boost version: {}.{}.{}",
               BOOST_VERSION/100000, BOOST_VERSION/100%1000,
               BOOST_VERSION%100);

  // Find out what kernel we are running
  KernelDetails kd;
  spdlog::info("{} {}.{}.{}", kd.os, kd.kernel_major, kd.kernel_minor,
               kd.kernel_patch);

  const char* path = getenv("XDG_RUNTIME_DIR");
  if (path==nullptr) {
    spdlog::error(get_error("no XDG_RUNTIME_DIR in env"));
    return EXIT_FAILURE;
  }

  const std::string templ { "wayland-wilde-XXXXXX"};

  std::filesystem::path xdg_dir(path);
  xdg_dir.append(templ);

  spdlog::info("Temporary memfd: {}", xdg_dir.string());

  int fd = mkostemp(xdg_dir.c_str(), O_CLOEXEC);
  if (fd >= 0)
    unlink(xdg_dir.c_str());



  spdlog::info("Shutting down...");
}