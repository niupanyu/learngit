#include <boost/pool/object_pool.hpp>
#include <iostream>

int main()
{
	int i;

    boost::object_pool<int> pool;
	pool.construct();
    std::cout << pool.get_next_size() << std::endl;
    pool.set_next_size(8);
    
    
	return 0;
}
