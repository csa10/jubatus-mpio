// Copyright (C) 2013 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.

#include <jubatus/mp/wavy.h>
#include <jubatus/mp/functional.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace mp::placeholders;

bool timer_handler(int* count, mp::wavy::loop* lo)
{
	try {
		std::cout << "*" << std::flush;
		if(--(*count) < 0) {
			lo->end();
		}
		else {
		    lo->add_timer(0.001, 0, mp::bind(&timer_handler, count, lo));
		}
		return false;
	}
	catch (std::exception& e) {
		std::cerr <<  e.what() << std::endl;
		std::exit(1);
	}
}

int main(void)
{
	mp::wavy::loop lo;
	int count = 2000;
	lo.add_timer(0.01, 0, mp::bind(
				&timer_handler, &count, &lo));
	lo.run(4);
	std::cout << std::endl;
}
