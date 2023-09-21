#include "Base/RNG/IRNG.h"


using namespace Steele;


template<> int IRNG::next<int>() { return next_int_32(); }
template<> float IRNG::next<float>() { return (float) next_double(); }
template<> double IRNG::next<double>() { return next_double(); }
template<> uint64_t IRNG::next<uint64_t>() { return next_uint_64(); }

template<> int IRNG::next<int>(int min, int max) { return next_int_32(min, max); }
template<> float IRNG::next<float>(float min, float max) { return (float) next_double(min, max); }
template<> double IRNG::next<double>(double min, double max) { return next_double(min, max); }
template<> uint64_t IRNG::next<uint64_t>(uint64_t min, uint64_t max) { return next_uint_64(min, max); }