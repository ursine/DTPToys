//
// Created by bear on 5/3/20.
//

#include "systemdetails.h"

KernelDetails::KernelDetails():
  kernel_major(0), kernel_minor(0), kernel_patch(0),
  release(""), os("")
{
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