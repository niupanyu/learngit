#include <boost/bimap.hpp>
#include <string>
#include <iostream>

void bimap_func()
{
    typedef boost::bimap<std::string, int> bimap;
	bimap animals;
	animals.insert({"cat", 4});
	animals.insert({"shark", 0});
	animals.insert({"spider", 8});
	
	std::cout << animals.left.count("cat") << "\n";
	std::cout << animals.right.count(8) << "\n";

	for( auto it = animals.begin(); it != animals.end(); ++it)
		std::cout << it->left << " has " << it->right << " legs\n";
}
