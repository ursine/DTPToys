//
// Created by bear on 5/3/20.
//

#pragma once

constexpr int SUCCESS_RESULT = 0;
constexpr int FAIL_RESULT = -1;

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

