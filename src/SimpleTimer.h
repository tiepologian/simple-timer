/*
 * SimpleTimer.h
 *
 *  Created on: Sep 23, 2015
 *      Author: Gianluca Tiepolo <tiepolo.gian@gmail.com>
 */

#ifndef SIMPLETIMER_H_
#define SIMPLETIMER_H_

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <mutex>
#include <map>

namespace simpletimer {

typedef std::chrono::microseconds micro;
typedef std::chrono::milliseconds ms;
typedef std::chrono::seconds sec;
typedef std::chrono::time_point<std::chrono::system_clock> sysClock;

/*
 * SimpleTimer class
 */
class SimpleTimer {
public:
	virtual ~SimpleTimer() {
	}
	static SimpleTimer& get() {
		static SimpleTimer instance;
		return instance;
	}
	void start(std::string timerName) {
#ifdef __linux__
		std::lock_guard<std::mutex> lock(_mutex);
#endif
		std::get<0>(_timers[timerName]) = std::chrono::system_clock::now();
	}
	void stop(std::string timerName) {
#ifdef __linux__
		std::lock_guard<std::mutex> lock(_mutex);
#endif
		if (_timers.find(timerName) == _timers.end()) {
			std::cout << "Timer \"" << timerName << "\" not found" << std::endl;
			exit(1);
		}
		std::get<1>(_timers[timerName]) = std::chrono::system_clock::now();
	}
	template<typename T>
	T getTime(std::string timerName) {
#ifdef __linux__
		std::lock_guard<std::mutex> lock(_mutex);
#endif
		if (_timers.find(timerName) == _timers.end()) {
			std::cout << "Timer \"" << timerName << "\" not found" << std::endl;
			exit(1);
		}
		T result = std::chrono::duration_cast<T>(std::get<1>(_timers[timerName]) - std::get<0>(_timers[timerName]));
		return result;
	}
private:
	SimpleTimer() {}
	SimpleTimer(const SimpleTimer& src);
	SimpleTimer& operator=(const SimpleTimer& rhs);
	std::map<std::string, std::pair<sysClock, sysClock>> _timers;
#ifdef __linux__
	std::mutex _mutex;
#endif
}; /* SimpleTimer class */

std::ostream &operator<<(std::ostream &os, const simpletimer::micro &obj) {
	return os << obj.count();
}

std::ostream &operator<<(std::ostream &os, const simpletimer::ms &obj) {
	return os << obj.count();
}

std::ostream &operator<<(std::ostream &os, const simpletimer::sec &obj) {
	return os << obj.count();
}

} /* namespace simpletimer */

#endif /* SIMPLETIMER_H_ */
