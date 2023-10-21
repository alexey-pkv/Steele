#ifndef STEELE_COMMON_H
#define STEELE_COMMON_H


#include <string>
#include "godot_cpp/variant/string.hpp"


inline std::string to_std_str(const godot::String& s) { return s.utf8().get_data(); }
inline godot::String to_godot_str(const std::string& s) { return s.c_str(); }


#endif