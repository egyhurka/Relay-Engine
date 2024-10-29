#include "Loader.h"

void Loader::simple(unsigned int count, bool stopwatch, std::function<void()> function){
    std::optional<TimeManager::stopwatch> stw;

    if (stopwatch) {
        stw.emplace();
        stw->start();
    }

    for (int i = 0; i < count; i++) {
        function();
    }
    std::cout << "ENGINE::INSTANCES::LOADED" << std::endl;
    std::cout << "ENGINE::LOADER::MODE:SIMPLE" << std::endl;

    if (stopwatch) {
        stw->stop();
        std::cout << "ENGINE::LOADER::MODE:SIMPLE::ELAPSED_TIME: " << stw->getElapsedTime() << " seconds" << std::endl;
    }
}

void Loader::batch(unsigned int count,unsigned int batchSize, bool stopwatch, std::function<void(int i)> function) {
    std::optional<TimeManager::stopwatch> stw;
    
    if (stopwatch) {
        stw.emplace();
        stw->start();
    }

    for (int i = 0; i < count; i += batchSize) {
        for (int j = 0; j < batchSize && (i + j) < count; ++j) {
            function(i + j);
        }
        std::cout << "ENGINE::INSTANCES::LOADED " << std::min(i + batchSize, count) << " OUT OF " << count << std::endl;
    }
    std::cout << "ENGINE::LOADER::MODE:BATCH" << std::endl;
    
    if (stopwatch) {
        stw->stop();
        std::cout << "ENGINE::LOADER::MODE:BATCH::ELAPSED_TIME: " << stw->getElapsedTime() << " seconds" << std::endl;
    }
}

int Loader::batchSizeCalculator(unsigned int count) {
    return count != 0 ? (int)(count / 100) * 5 : 1;
}