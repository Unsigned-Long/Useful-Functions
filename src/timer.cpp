//
// Created by csl on 5/11/23.
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#define LOCK_TIMER_STATUS std::unique_lock<std::mutex> timerStatusLock(Timer::_mt);

class Timer {
public:
    using Ptr = std::shared_ptr<Timer>;

protected:
    boost::asio::io_service _io;
    std::shared_ptr<std::thread> _thread;
    bool _shouldQuit;
    static std::mutex _mt;

public:
    Timer(const std::function<void()> &fun, int ms) : _shouldQuit(false) {
        _thread = std::make_shared<std::thread>([&fun, ms, this]() {
            StartTimer(_io, fun, ms);
        });
    }

    static Ptr Create(const std::function<void()> &fun, int ms) {
        return std::make_shared<Timer>(fun, ms);
    }

    void Quit() {
        LOCK_TIMER_STATUS
        this->_shouldQuit = true;
    }

    virtual ~Timer() {
        _thread->join();
    }

protected:
    void StartTimer(boost::asio::io_service &io, const std::function<void()> &fun, int ms) {
        bool status;
        {
            LOCK_TIMER_STATUS
            status = _shouldQuit;
        }
        if (status) {
            io.stop();
        } else {
            boost::asio::deadline_timer t(io, boost::posix_time::milliseconds(ms));
            t.async_wait(boost::bind(&Timer::StartTimer, this, boost::ref(io), std::ref(fun), ms));
            fun();
            io.run();
        }
    }
};

std::mutex Timer::_mt = {};

#include "iostream"

void handler() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    Timer t(handler, 500);
    std::cin.get();
    t.Quit();
    return 0;
}

