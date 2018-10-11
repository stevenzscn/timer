#ifndef _TIME_UTIL_H_
#define _TIME_UTIL_H_

#include <inttypes.h>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>

class ClockTime {
    public:
        void start() {
            total_time_ = 0;
            is_runing_ = true;
            start_ = std::chrono::system_clock::now();
        }

        void resume() {
            is_runing_ = true;
            start_ = std::chrono::system_clock::now();
        }

        uint64_t stop() {
            if (!is_runing_)
                return total_time_;

            stop_ = std::chrono::system_clock::now();
            total_time_ +=
                std::chrono::duration_cast<std::chrono::microseconds>(stop_ - start_).count();
            is_runing_ = false;

            return total_time_;
        }

        uint64_t get_time() {
            if (!is_runing_)
                return total_time_;

            auto tmp = std::chrono::system_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(tmp - start_).count();
        }

    private:
        std::chrono::system_clock::time_point start_;
        std::chrono::system_clock::time_point stop_;
        uint64_t total_time_ = 0;
        bool is_runing_ = false;
};

class TimeUtil {
    public:
        static std::string get_time_now() {
            std::stringstream ss;
            auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            ss << std::put_time(std::localtime(&t), "%Y-%m-%d %X");
            return ss.str();
        }
};

#endif
