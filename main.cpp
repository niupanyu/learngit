#include <unistd.h>
#include <string.h>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/random/random_device.hpp>
#include <iostream>

#include "bimap_func.h"
struct int_pool{};
typedef boost::singleton_pool<int_pool, sizeof(int)> singleton_int_pool;

void func_pool2()
{
	boost::random::random_device gen;
	while(true)
	{
		unsigned size = gen()%100000;

		char *p = (char*)malloc(size);
		memset(p, 0xffff, size);
		free(p);
	}
}

void func_pool()
{
	const int cbElem = sizeof(int);
	boost::pool<> alloc(cbElem);
	unsigned loop = 0;
	while(1)
	{
		int *p = (int*) alloc.malloc();
		*p = loop%1000;
		alloc.free(p);
		if(loop % 1000 == 0)
		    sleep(3);

		loop++;
			
	}
}


int main()
{
    bimap_func();
	return 0;

    boost::object_pool<int> pool{32, 0};
	std::cout << sizeof(pool) << std::endl;
	pool.construct();
    std::cout << sizeof(pool) << std::endl;
	std::cout << pool.get_next_size() << std::endl;
    pool.set_next_size(8);
    
    
	return 0;
}
