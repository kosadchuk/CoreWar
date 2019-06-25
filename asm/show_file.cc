#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int		main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	std::ifstream ifd(av[1], std::ios::binary | std::ios::ate);
	int size = ifd.tellg();
	ifd.seekg(0, std::ios::beg);
	std::vector<unsigned char> buffer;
	buffer.resize(size);
	ifd.read((char *)buffer.data(), size);

	for (int i = 2192; i < buffer.size(); ++i)
	{
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)buffer[i];
		if (i % 2 && i != 2192)
			std::cout << std::endl;
	}
	std::cout << "\n";

	//std::cout.write(buffer.data(), buffer.size());
	return (0);
}