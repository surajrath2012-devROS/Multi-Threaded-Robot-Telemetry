#include "SensorModule.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>

namespace RobotApp
{
    // The "Landmark" - building the buffer and key in memory
    std::deque<double> sensorBuffer;
    std::mutex bufferMutex;

    void runProducer()
    {
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<> dis(20.0, 30.0); 

        while(true)
        {
            double temp = dis(gen);
            { 
                std::lock_guard<std::mutex> lock(bufferMutex);
                sensorBuffer.push_back(temp); 
                std::cout << "[SENSOR] : Captured Telemetry: " << temp << "°C" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void runConsumer()
    {
        while(true)
        {
            if(!sensorBuffer.empty())
            {
                std::lock_guard<std::mutex> lock(bufferMutex);
                double data = sensorBuffer.front();
                sensorBuffer.pop_front();
                std::cout << "[ANALYST] : Analysis Complete for: " << data << "°C" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void runDisplay() {
        while (true) {
            {
                // We grab the key just to count the messages
                std::lock_guard<std::mutex> lock(bufferMutex);
                
                std::cout << "------------------------------------" << std::endl;
                std::cout << "[DASHBOARD] : Messages in Pipe: " << sensorBuffer.size() << std::endl;
                if (!sensorBuffer.empty()) {
                    std::cout << "[DASHBOARD] : Latest Value: " << sensorBuffer.back() << "°C" << std::endl;
                }
                std::cout << "------------------------------------" << std::endl;
            }

            // The Display only needs to update once per second
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    
}