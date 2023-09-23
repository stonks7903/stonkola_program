#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <format>


void gbinfo(std::vector<std::byte> hexdata)
{
	bool isgbcused;
	std::cout << "Gameboy ROM Info:\n";
	if (std::to_integer<int>(hexdata[0x101]) != 0xc3)
	{
		std::cout << "The ROM does not have a jp instruction at 0x100. The gameboy will try to read 0x104-0x14f (Undefined behavior)\n";
	}
	else
	{
		std::cout << std::format("Code execution will begin at 0x{:x}{:x}\n",std::to_integer<int>(hexdata[0x103]),std::to_integer<int>(hexdata[0x102]));
	}
	if (std::to_integer<int>(hexdata[0x143]) == 0x80 || std::to_integer<int>(hexdata[0x143]) == 0xc0)
	{
		isgbcused = true;
		if (std::to_integer<int>(hexdata[0x143]) == 0x80)
		{
			std::cout << "This ROM uses GBC functions but will still work on old gameboys.\n";
		}
		else
		{
			std::cout << "This ROM uses GBC functions and will not work on old gameboys.\n";
		}
	}
	std::cout << "The internal name / Manufacturer Code of the ROM is: ";
	for (int i = 0x134;i<=0x143-isgbcused;i++)
	{
		std::cout << std::to_integer<char>(hexdata[i]);
	}
	std::cout << std::endl;
	if (std::to_integer<int>(hexdata[0x146]) == 0x03)
	{
		std::cout << "SGB Functions will work on this ROM.\n";
	}
	else
	{
		std::cout << "This rom does not support SGB Functions.\n";
	}
	std::cout << "Hardware type: ";
	switch (std::to_integer<int>(hexdata[0x147]))
	{
		case 0x0:
			std::cout << "ROM ONLY\n";
			break;
		case 0x01:
			std::cout << "MBC1\n";
			break;
		case 0x02:
			std::cout << "MBC1+RAM\n";
			break;
		case 0x03:
			std::cout << "MBC1+RAM+BATTERY\n";
			break;
		case 0x05:
			std::cout << "MBC2\n";
			break;
		case 0x06:
			std::cout << "MBC2+BATTERY\n";
			break;
		case 0x08:
			std::cout << "ROM+RAM\n";
			break;
		case 0x09:
			std::cout << "ROM+RAM+BATTERY\n";
			break;
		case 0x0B:
			std::cout << "MMM01\n";
			break;
		case 0x0C:
			std::cout << "MMM01+RAM\n";
			break;
		case 0x0D:
			std::cout << "MMM01+RAM+BATTERY\n";
			break;
		case 0x0F:
			std::cout << "MBC3+TIMER+BATTERY\n";
			break;
		case 0x10:
			std::cout << "MBC3+TIMER+RAM+BATTERY\n";
			break;
		case 0x11:
			std::cout << "MBC3\n";
			break;
		case 0x12:
			std::cout << "MBC3+RAM\n";
			break;
		case 0x13:
			std::cout << "MBC3+RAM+BATTERY\n";
			break;
		case 0x19:
			std::cout << "MBC5\n";
			break;
		case 0x1A:
			std::cout << "MBC5+RAM\n";
			break;
		case 0x1B:
			std::cout << "MBC5+RAM+BATTERY\n";
			break;
		case 0x1C:
			std::cout << "MBC5+RUMBLE\n";
			break;
		case 0x1D:
			std::cout << "MBC5+RUMBLE+RAM\n";
			break;
		case 0x1E:
			std::cout << "MBC5+RUMBLE+RAM+BATTERY\n";
			break;
		case 0x20:
			std::cout << "MBC6\n";
			break;
		case 0x22:
			std::cout << "MBC7+SENSOR+RUMBLE+RAM+BATTERY\n";
			break;
		case 0xFC:
			std::cout << "POCKEt CAMERA\n";
			break;
		case 0xFD:
			std::cout << "BANDAI TAMAS\n";
			break;
		case 0xFE:
			std::cout << "HuC3\n";
			break;
		case 0xFF:
			std::cout << "HuC1+RAM+BATTERY\n";
			break;
	}
	std::cout << "The ROM size is: ";
	switch(std::to_integer<int>(hexdata[0x148]))
	{
		case 0x00:
			std::cout << "32 KiB\n";
			break;
		case 0x01:
			std::cout << "64 KiB\n";
			break;
		case 0x02:
			std::cout << "128 KiB\n";
			break;
		case 0x03:
			std::cout << "256 KiB\n";
			break;
		case 0x04:
			std::cout << "512 KiB\n";
			break;
		case 0x05:
			std::cout << "1 MiB\n";
			break;
		case 0x06:
			std::cout << "2 MiB\n";
			break;
		case 0x07:
			std::cout << "4 MiB\n";
			break;
		case 0x08:
			std::cout << "8 MiB\n";
			break;
	}
	std::cout << "The RAM size is: ";
	switch(std::to_integer<int>(hexdata[0x149]))
	{
		case 0x00:
			std::cout << "No Ram\n";
			break;
		case 0x02:
			std::cout << "8 KiB\n";
			break;
		case 0x03:
			std::cout << "32 KiB\n";
			break;
		case 0x04:
			std::cout << "128 KiB\n";
			break;
		case 0x05:
			std::cout << "64 KiB\n";
			break;
	}
	std::cout << std::format("The ROM version is {}\n", std::to_integer<int>(hexdata[0x14c]));
	uint8_t checksum = 0;
	for (uint16_t address = 0x134; address <= 0x14C; address++)
	{
		checksum = checksum - std::to_integer<uint8_t>(hexdata[address]) - 1;
	}
	if (std::to_integer<uint8_t>(hexdata[0x14D]) == checksum)
	{
		std::cout << "The header checksum is valid.";
	}
	else
	{
		std::cout << std::format("The header checksum is invalid. The correct checksum is {:#x}\n",checksum);
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
