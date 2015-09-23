/*
 * main.cpp
 *
 *  Created on: Sep 23, 2015
 *      Author: Gianluca Tiepolo <tiepolo.gian@gmail.com>
 */

#include "SimpleTimer.h"

using namespace simpletimer;

/*
 * A utility function that wastes some time
 */
void wasteSomeTime() {
	for (int i = 0; i < 100 * 1000; i++) {
		char *tmp = new char[1024];
		delete tmp;
	}
}

int main(int argc, char* argv[]) {
	// Create two timers
	SimpleTimer::get().start("Timer #1");
	SimpleTimer::get().start("Timer #2");

	// Waste some time...
	wasteSomeTime();

	// Stop timer 1 and print elapsed time in milliseconds
	SimpleTimer::get().stop("Timer #1");
	std::cout << "Timer #1: " << SimpleTimer::get().getTime<ms>("Timer #1") << " ms" << std::endl;

	// Waste more time...
	wasteSomeTime();

	// Stop timer 2 and print elapsed time in micro-seconds
	SimpleTimer::get().stop("Timer #2");
	std::cout << "Timer #2: " << SimpleTimer::get().getTime<micro>("Timer #2") << " micro" << std::endl;

	return 0;
}
