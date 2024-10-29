#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <functional>
#include <optional>

#include "../../Utilities/Time/TimeManager.h"

class Loader {
public:
	static void simple(unsigned int count, bool stopwatch, std::function<void()> function);
	static void batch(unsigned int count, unsigned int batchSize, bool stopwatch, std::function<void(int i)> function);
	static int batchSizeCalculator(unsigned int count);
};

#endif // !LOADER_H
