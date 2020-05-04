//
// Created by bear on 5/3/20.
//

#pragma once

#include <sys/utsname.h>
#include <string>
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>
#include <system_error>
#include <vector>
#include "globalutils.h"

class SystemDetails {

};


class KernelDetails {
private:
  utsname kernel_details {};
public:
  long kernel_major;
  long kernel_minor;
  long kernel_patch;
  std::string release;
  std::string os;

  KernelDetails();
  ~KernelDetails() = default;
};
