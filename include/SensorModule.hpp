#pragma once
#include <deque>
#include <mutex>

namespace RobotApp
{
    // We put 'extern' because we are telling other files:
    // "The plate exists, but it's kept in the main kitchen (the .cpp file)"
    extern std::deque<double> sensorBuffer;
    extern std::mutex bufferMutex;

    void runProducer();
    void runConsumer();
    void runDisplay();
}