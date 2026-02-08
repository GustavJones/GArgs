#pragma once
#include <string>

namespace GArgs {
  template<typename version_t>
  struct Version {
    version_t Major;
    version_t Minor;
    version_t Patch;

    operator std::string() {
      std::string out;
      out += 'V';
      out += std::to_string(Major);
      out += '.';
      out += std::to_string(Minor);
      out += '.';
      out += std::to_string(Patch);
      return out;
    };
  };
}
