#include <sys/mman.h>
#include <spdlog/spdlog.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include "globalutils.h"
#include "systemdetails.h"
#include "WaylandManager.h"
#include <boost/version.hpp>


extern "C"
void _c_log_handler(const char *format, va_list args)
{
  // Format string
  va_list args_copy;

  // vsnprintf consumes args, so copy beforehand
  va_copy(args_copy, args);
  int length = std::vsnprintf(nullptr, 0, format, args);
  if(length < 0)
  {
    va_end(args_copy);
    throw std::runtime_error("Error getting length of formatted wayland-client log message");
  }

  // check for possible overflow - could be done at runtime but the following should hold on all usual platforms
  static_assert(std::numeric_limits<std::vector<char>::size_type>::max() >= std::numeric_limits<int>::max() + 1U /* NUL */,
                "vector constructor must allow size big enough for vsnprintf return value");

  // for terminating NUL
  length++;

  std::vector<char> buf(static_cast<std::vector<char>::size_type>(length));
  if(std::vsnprintf(buf.data(), buf.size(), format, args_copy) < 0)
    throw std::runtime_error("Error formatting wayland-client log message");

  va_end(args_copy);

  spdlog::info(buf.data());
}


int main(int argc, char* argv[]) {
  spdlog::info("Booting up... (spdlog version {}.{}.{})",
               SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

  spdlog::info("Boost version: {}.{}.{}",
               BOOST_VERSION/100000, BOOST_VERSION/100%1000,
               BOOST_VERSION%100);

  wl_log_set_handler_client(_c_log_handler);

  // Find out what kernel we are running
  KernelDetails kd;
  spdlog::info("{} {}.{}.{}", kd.os, kd.kernel_major, kd.kernel_minor,
               kd.kernel_patch);

//  const char* path = getenv("XDG_RUNTIME_DIR");
//  if (path==nullptr) {
//    spdlog::error(get_error("no XDG_RUNTIME_DIR in env"));
//    return EXIT_FAILURE;
//  }
//
//  const std::string templ { "wayland-wilde-XXXXXX"};
//
//  std::filesystem::path xdg_dir(path);
//  xdg_dir.append(templ);
//
//  spdlog::info("Temporary memfd: {}", xdg_dir.string());

  int fd = memfd_create("wayland-cursor", MFD_CLOEXEC | MFD_ALLOW_SEALING);
  if (fd >= 0) {
    fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
  }
  int size = 600;
#ifdef HAVE_POSIX_FALLOCATE
  /*
   * Filesystems that do support fallocate will return EINVAL or
   * EOPNOTSUPP. In this case we need to fall back to ftruncate
   */
  errno = posix_fallocate(fd, 0, size);
  if (errno == SUCCESS_RESULT)
          return SUCCESS_RESULT;
  else if (errno != EINVAL && errno != EOPNOTSUPP)
          return FAIL_RESULT;
#endif
  if (ftruncate(fd, size) < 0)
    return -1;

  wl::WaylandManager wm;


  spdlog::info("Shutting down...");
}