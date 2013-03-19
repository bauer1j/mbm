#include "common/config.h"

#include <sstream>
#include <string>

#include <assert.h>
#include <stdint.h>

namespace {
const std::string delimiter = ":";
}

Config::Config()
    : low_cbr_kb_s(0), high_cbr_kb_s(0), time_per_test(0) {
}

Config::Config(uint32_t low_cbr_kb_s, uint32_t high_cbr_kb_s,
               uint32_t time_per_test)
    : low_cbr_kb_s(low_cbr_kb_s), high_cbr_kb_s(high_cbr_kb_s),
      time_per_test(time_per_test) {
  assert(high_cbr_kb_s > low_cbr_kb_s);
}

std::string Config::AsString() const {
  std::ostringstream ss;
  ss << low_cbr_kb_s << delimiter << high_cbr_kb_s << delimiter <<
        time_per_test;
  return ss.str();
}

void Config::FromString(const std::string& str) {
  std::string::size_type last_pos = str.find_first_not_of(delimiter, 0);
  std::string::size_type pos = str.find_first_of(delimiter, last_pos);
  std::istringstream(str.substr(last_pos, pos - last_pos)) >>
      low_cbr_kb_s;
  
  last_pos = str.find_first_not_of(delimiter, pos);
  pos = str.find_first_of(delimiter, last_pos);
  std::istringstream(str.substr(last_pos, pos - last_pos)) >>
      high_cbr_kb_s;

  last_pos = str.find_first_not_of(delimiter, pos);
  pos = str.find_first_of(delimiter, last_pos);
  std::istringstream(str.substr(last_pos, pos - last_pos)) >>
      time_per_test;
}