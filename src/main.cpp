#include <iostream>
#include <thread>
#include "SensorModule.hpp"

int main() {
    std::cout << "!!! ROBOTIC TELEMETRY ENGINE ONLINE !!!" << std::endl;

    // Launching the 3-Chamber Heart
    std::thread producerThread(RobotApp::runProducer);
    std::thread consumerThread(RobotApp::runConsumer);
    std::thread displayThread(RobotApp::runDisplay);

    // Tell the Boss (Main) to wait for all of them
    producerThread.join();
    consumerThread.join();
    displayThread.join();

    return 0;
}