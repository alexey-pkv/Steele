#include "IRNG.h"


using namespace Steele::RNG;


template<> int IRNG::Next<int>() { return NextInt(); }
template<> float IRNG::Next<float>() { return (float)NextDouble(); }
template<> double IRNG::Next<double>() { return NextDouble(); }

template<> int IRNG::Next<int>(int min, int max) { return NextInt(min, max); }
template<> float IRNG::Next<float>(float min, float max) { return (float)NextDouble(min, max); }
template<> double IRNG::Next<double>(double min, double max) { return NextDouble(min, max); }