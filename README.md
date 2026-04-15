# 🫀 ThreadedHeart: High-Frequency Robotics Telemetry Engine

**ThreadedHeart** is a concurrent C++ system designed to simulate a high-performance robotics telemetry pipeline. It utilizes a multi-threaded architecture to decouple data acquisition, processing, and system monitoring, ensuring zero-latency sensor polling on high-core-count processors.

## 🏗️ System Architecture: The 3-Chamber Heart
The system operates on three parallel CPU cores using an "Eye-Brain-Display" model:

1. **The Eye (Producer):** A high-frequency thread generating simulated telemetry data (Temperature/Voltages) at 500ms intervals.
2. **The Brain (Consumer):** An asynchronous analyst thread that processes data at a faster rate (100ms) to ensure zero buffer overflow.
3. **The Display (Monitor):** A periodic observer thread that provides a real-time dashboard of the system's "Heartbeat" and pipe health.



## 🛠️ Technical Deep Dive

### ⚡ Why std::deque?
Unlike a `std::vector`, which requires expensive memory reallocations when removing items from the front, **std::deque** (Double-Ended Queue) is optimized for robotics pipelines. It allows for constant-time $O(1)$ insertions at the back and deletions at the front, making it the perfect "Tube" for sensor data.

### 🛡️ Thread Safety & Synchronization
To prevent **Race Conditions**, the system utilizes `std::mutex` and `std::lock_guard`. 
* **RAII Principles:** We use `std::lock_guard` to ensure that the Mutex (the key) is automatically released even if a thread encounters an error, preventing system-wide deadlocks.

### 🧪 Unit Testing
Validation is performed via **Google Test (GTest)**, covering:
* Buffer integrity checks.
* Thread-safe push/pop operations.

## 🚀 Build Instructions
```bash
mkdir build && cd build
cmake ..
make
./heart_engine
./run_tests
