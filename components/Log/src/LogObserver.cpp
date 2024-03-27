/**
 * @file LogObserver.cpp
 * @author Tymofiy Kovalenko
 * @date 21-Mar-2024
 * @brief
 */

#include <utility>

#include "../include/LogObserver.h"
#include <chrono>

LogObserver::LogObserver(const string &filename) : log(filename , std::ios::app) {
    write("Start logging");
}


void LogObserver::update(const string& message) {
    write(message);
}

void LogObserver::write(const string& message) {
    // NOTE Checks if this is not a nullptr. Ignore the warning, it works as intended.
    if (this == nullptr) {
        return;
    }
    if (log.is_open()) {
        auto now = chrono::system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(now);
        tm* local_tim = localtime(&now_c);
        auto milliseconds = duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
        log << put_time(local_tim, "%c") << ":" << setfill('0') << setw(3) << milliseconds.count() << "\t";
        log << message << std::endl;
        log.flush();
        cout << put_time(local_tim, "%c") << ":" << setfill('0') << setw(3) << milliseconds.count() << "\t";
        cout << message << std::endl;
    }
}
void LogObserver::update() {


}
