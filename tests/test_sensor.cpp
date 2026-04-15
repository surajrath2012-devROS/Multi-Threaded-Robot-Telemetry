#include <gtest/gtest.h>
#include "SensorModule.hpp"

// We are testing the "RobotApp" namespace
using namespace RobotApp;

// Test 1: Is the buffer empty at the start?
TEST(SensorBufferTest, InitiallyEmpty) {
    // We expect the size to be 0
    EXPECT_EQ(sensorBuffer.size(), 0);
}

// Test 2: If we push a telemetry, does it stay there?
TEST(SensorBufferTest, PushesDataCorrectly) {
    double testValue = 25.5;
    
    // We grab the key manually for the test
    {
        std::lock_guard<std::mutex> lock(bufferMutex);
        sensorBuffer.push_back(testValue);
    }
    
    EXPECT_EQ(sensorBuffer.size(), 1);
    EXPECT_EQ(sensorBuffer.front(), 25.5);
    
    // Clean up for the next test
    sensorBuffer.pop_front();
}