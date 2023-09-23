#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <format>
#define NINTENDO_LOGO = 0xceed6666cc0d000b03730083000c000d0008111f8889000edccc6ee6ddddd999bbbb67636e0eecccdccc999fbbb9333e


void gbinfo(std::vector<std::byte> hexdata)
{
	std::cout << "Gameboy ROM Info:\n";
	if (std::to_integer<int>(hexdata[0x101]) != 0xc3)
	{
		std::cout << "The ROM does not have a jp instruction at 0x100. The gameboy will try to read 0x104-0x14f (Undefined behavior)\n";
	}
	else
	{
		std::cout << std::format("Code execution will begin at 0x{:x}{:x}\n",std::to_integer<int>(hexdata[0x103]),std::to_integer<int>(hexdata[0x102]));
	}
	return;

}

int main()
{
	std::string filename;
	std::cout << "Enter your GB/GBC game rom filename: ";
	std::cin >> filename;
	std::ifstream gbrom;
	gbrom.open(filename,std::fstream::in | std::fstream::binary | std::fstream::ate);
	std::streampos filesize = gbrom.tellg();
	std::vector<std::byte> hexdata;
	hexdata.resize(filesize);
	gbrom.seekg(0);
	gbrom.read(reinterpret_cast<char*>(&hexdata[0]),filesize);
	gbrom.close();
	gbinfo(hexdata);
	return 0;

}
