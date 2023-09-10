#include "IRNG.h"


using namespace Steele::RNG;


template<> int IRNG::next<int>() { return next_int_32(); }
template<> float IRNG::next<float>() { return (float) next_double(); }
template<> double IRNG::next<double>() { return next_double(); }

template<> int IRNG::Next<int>(int min, int max) { return next_int_32(min, max); }
template<> float IRNG::Next<float>(float min, float max) { return (float) next_double(min, max); }
template<> double IRNG::Next<double>(double min, double max) { return next_double(min, max); }