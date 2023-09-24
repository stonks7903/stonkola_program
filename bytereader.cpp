#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <format>
#include <map>
#include <string_view>
int gbinfo(std::vector<std::byte> hexdata)
{
	int pc_start;
	int isgbcused=0;
	std::cout << "Gameboy ROM Info:\n";
	if (std::to_integer<int>(hexdata[0x101]) != 0xc3)
	{
		std::cout << "The ROM does not have a jp instruction at 0x100. The gameboy will try to read 0x104-0x14f (Undefined behavior)\n";
	}
	else
	{
		std::cout << std::format("Code execution will begin at 0x{:x}{:x}\n",std::to_integer<int>(hexdata[0x103]),std::to_integer<int>(hexdata[0x102]));
		pc_start = (std::to_integer<int>(hexdata[0x103]) << 8) + std::to_integer<int>(hexdata[0x102]);
	}
	if (std::to_integer<int>(hexdata[0x143]) == 0x80 || std::to_integer<int>(hexdata[0x143]) == 0xc0)
	{
		isgbcused = 1;
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
		std::cout << "The header checksum is valid.\n";
	}
	else
	{
		std::cout << std::format("The header checksum is invalid. The correct checksum is {:#x}\n",checksum);
	}
	return pc_start;

}

struct asmdata
{
	std::string mnemonic;
	bool is_16bit;
	int instr_size;
	bool is_signed = false;
};
void gbdisasm(int pc, std::vector<std::byte> hexdata)
{
	std::map<int,asmdata> asmtable{{0x00,{"NOP",false,1}},{0x01,{"ld BC {:#x}{:x}",true,3}},{0x02,{"ld [BC], A", false,1}},{0x03,{"inc BC",true,1}},
					{0x04,{"inc B",false,1}}, {0x05,{"dec B", false,1}},{0x06,{"ld B, {:#x}",false,1}},{0x07,{"RLCA",false,1}},
					{0x08,{"ld [{:#x}{:x}], SP",true,3}},{0x09,{"add HL, BC",true,1}},{0x0A,{"ld A, [BC]",false,1}},{0x0B,{"dec BC",true,1}},
					{0x0C,{"inc C",false,1}},{0x0D,{"dec C",false,1}},{0x0E,{"ld C, {:#x}",false,2}},{0x0F,{"RRCA",false,1}},
					{0x10,{"STOP",false,1}}, {0x11, {"ld DE, {:#x}{:x}",true,3}},{0x12,{"ld [DE], A",false,1}}, {0x13,{"inc DE",true,1}},
					{0x14,{"inc D",false,1}},{0x15,{"dec D",false,1}},{0x16,{"ld D, {:#x}",false,2}},{0x17,{"RLA",false,1}},
					{0x18,{"jr {:#x}",false,2,true}},{0x19,{"add HL, DE", true, 1}}, {0x1A,{"ld A, [DE]",false,1}},{0x1B,{"dec DE",false,1}},
					{0x1C,{"inc E",false,1}},{0x1D,{"dec E",false,1}},{0x1E,{"ld E {:#x}",false,2}},{0x1F,{"RRA",false,1}},
					{0x20,{"jr NZ, {:#x}",false,2,true}},{0x21,{"ld HL {:#x}{:x}",true,3}},{0x22,{"ld [HL+], A",false,1}},{0x23,{"inc HL",true,1}},
					{0x24,{"inc H",false,1}},{0x25,{"dec H",false,1}},{0x26,{"ld [HL], {:#x}",false,2}},{0x27,{"daa",false,1}},
					{0x28,{"jr Z, {:#x}",false,2,true}},{0x29,{"add HL, SP",true,1}},{0x2A,{"ld A, [HL+]",false,1}},{0x2B,{"dec HL",true,1}},
					{0x2C,{"inc L",false,1}},{0x2D,{"dec L",false,1}},{0x2E,{"ld L, {:#x}",false,2}},{0x2F,{"CPL",false,1}},
					{0x30,{"jr NC, {:#x}",false,2,true}},{0x31,{"ld SP {:#x}{:#x}",true,3}},{0x32,{"ld [HL-], A",false, 1}},{0x33,{"inc SP",true,1}},
					{0x34,{"inc [HL]",false,1}},{0x35,{"dec [HL]",false,1}},{0x36,{"ld [HL], {:#x}",false,2}},{0x37,{"SFC",false,1}},
					{0x38,{"jr C, {:#x}",false,2}},{0x39,{"add HL, SP",true,1}},{0x3A,{"ld A, [HL-]",false,1}},{0x3B,{"dec SP",true,1}},
					{0x3C,{"inc A", false,1}},{0x3D,{"dec A",false,1}},{0x3E,{"ld A, {:#x}",false,2}},{0x3F,{"CCF",false,1}},
					{0x40,{"ld B, B",false,1}},{0x41,{"ld B, C",false,1}},{0x42,{"ld B, D",false,1}},{0x43,{"ld B, E",false,1}},
					{0x44,{"ld B, H",false,1}},{0x45,{"ld B, L",false,1}},{0x46,{"ld B, [HL]",false,1}},{0x47,{"ld B, A",false,1}},
					{0x48,{"ld C, B",false,1}},{0x49,{"ld C, C",false,1}},{0x4A,{"ld C, D",false,1}},{0x4B,{"ld C, E",false,1}},
					{0x4C,{"ld C, H",false,1}},{0x4D,{"ld C, L",false,1}},{0x4E,{"ld C, [HL]",false,1}},{0x4F,{"ld C, A",false,1}},
					{0x50,{"ld D, B",false,1}},{0x51,{"ld D, C",false,1}},{0x52,{"ld D, D",false,1}},{0x53,{"ld D, E",false,1}},
					{0x54,{"ld D, H",false,1}},{0x55,{"ld D, L",false,1}},{0x56,{"ld D, [HL]",false,1}},{0x57,{"ld D, A",false,1}},
					{0x58,{"ld E, B",false,1}},{0x59,{"ld E, C",false,1}},{0x5A,{"ld E, D",false,1}},{0x5B,{"ld E, E",false,1}},
					{0x5C,{"ld E, H",false,1}},{0x5D,{"ld E, L",false,1}},{0x5E,{"ld E, [HL]",false,1}},{0x5F,{"ld E, A",false,1}},
					{0x60,{"ld H, B",false,1}},{0x61,{"ld H, C",false,1}},{0x62,{"ld H, D",false,1}},{0x63,{"ld H, E",false,1}},
					{0x64,{"ld H, H",false,1}},{0x65,{"ld H, L",false,1}},{0x66,{"ld H, [HL]",false,1}},{0x67,{"ld H, A",false,1}},
					{0x68,{"ld L, B",false,1}},{0x69,{"ld L, C",false,1}},{0x6A,{"ld L, D",false,1}},{0x6B,{"ld L, E",false,1}},
					{0x6C,{"ld L, H",false,1}},{0x6D,{"ld L, L",false,1}},{0x6E,{"ld L, [HL]",false,1}},{0x6F,{"ld L, A",false,1}},
					{0x70,{"ld [HL], B",false,1}},{0x71,{"ld [HL], C",false,1}},{0x72,{"ld [HL], D",false,1}},{0x73,{"ld [HL], E",false,1}},
					{0x74,{"ld [HL], H",false,1}},{0x75,{"ld [HL], L",false,1}},{0x76,{"HALT",false,1}},{0x77,{"ld [HL], A",false,1}},
					{0x78,{"ld A, B",false,1}},{0x79,{"ld A, C",false,1}},{0x7A,{"ld A, D",false,1}},{0x7B,{"ld A, E",false,1}},
					{0x7C,{"ld A, H",false,1}},{0x7D,{"ld A, L",false,1}},{0x7E,{"ld A, [HL]",false,1}},{0x7F,{"ld A, A",false,1}},
					{0x80,{"add A, B",false,1}},{0x81,{"add A, C",false,1}},{0x82,{"add A, D",false,1}},{0x83,{"add A, E",false,1}},
					{0x84,{"add A, H",false,1}},{0x85,{"add A, L",false,1}},{0x86,{"add A, [HL]",false,1}},{0x87,{"add A, A",false,1}},
					{0x88,{"adc A, B",false,1}},{0x89,{"adc A, C",false,1}},{0x8A,{"adc A, D",false,1}},{0x8B,{"adc A, E",false,1}},
					{0x8C,{"adc A, H",false,1}},{0x8D,{"adc A, L",false,1}},{0x8E,{"adc A, [HL]",false,1}},{0x8F,{"adc A, A",false,1}},
					{0x90,{"sub A, B",false,1}},{0x91,{"sub A, C",false,1}},{0x92,{"sub A, D",false,1}},{0x93,{"sub A, E",false,1}},
					{0x94,{"sub A, H",false,1}},{0x95,{"sub A, L",false,1}},{0x96,{"sub A, [HL]",false,1}},{0x97,{"sub A, A",false,1}},
					{0x98,{"sbc A, B",false,1}},{0x99,{"sbc A, C",false,1}},{0x9A,{"sbc A, D",false,1}},{0x9B,{"sbc A, E",false,1}},
					{0x9C,{"sbc A, H",false,1}},{0x9D,{"sbc A, L",false,1}},{0x9E,{"sbc A, [HL]",false,1}},{0x9F,{"sbc A, A",false,1}},
					{0xA0,{"and A, B",false,1}},{0xA1,{"and A, C",false,1}},{0xA2,{"and A, D",false,1}},{0xA3,{"and A, E",false,1}},
					{0xA4,{"and A, H",false,1}},{0xA5,{"and A, L",false,1}},{0xA6,{"and A, [HL]",false,1}},{0xA7,{"and A, A",false,1}},
					{0xA8,{"xor A, B",false,1}},{0xA9,{"xor A, C",false,1}},{0xAA,{"xor A, D",false,1}},{0xAB,{"xor A, E",false,1}},
					{0xAC,{"xor A, H",false,1}},{0xAD,{"xor A, L",false,1}},{0xAE,{"xor A, [HL]",false,1}},{0xAF,{"xor A, A",false,1}},
					{0xB0,{"or A, B",false,1}},{0xB1,{"or A, C",false,1}},{0xB2,{"or A, D",false,1}},{0xB3,{"or A, E",false,1}},
					{0xB4,{"or A, H",false,1}},{0xB5,{"or A, L",false,1}},{0xB6,{"or A, [HL]",false,1}},{0xB7,{"or A, A",false,1}},
					{0xB8,{"cp A, B",false,1}},{0xB9,{"cp A, C",false,1}},{0xBA,{"cp A, D",false,1}},{0xBB,{"cp A, E",false,1}},
					{0xBC,{"cp A, H",false,1}},{0xBD,{"cp A, L",false,1}},{0xBE,{"cp A, [HL]",false,1}},{0xBF,{"cp A, A",false,1}},
					{0xC0,{"ret NZ",false,1}},{0xC1,{"pop BC",true,1}},{0xC2,{"jp NZ, {:#x}{:x}",true,3}},{0xC3,{"jp {:#x}{:#x}",true,3}},
					{0xC4,{"call NZ, {:#x}{:x}",true,3}},{0xC5,{"push BC",true,1}},{0xC6,{"add A, {:#x}",false,2}},{0xC7,{"rst 0x00",false,1}},
					{0xC8,{"ret Z",false,1}},{0xC9,{"ret",false,1}},{0xCA,{"jp Z, {:#x}{:x}",true,3}},                
					{0xCC,{"call Z, {:#x}{:x}",true,3}},{0xCD,{"call {:#x}{:x}",true,3}},{0xCE,{"adc A, {:#x}",false,2}},{0xCF,{"rst 0x08",false,1}},
					{0xD0,{"ret NC",false,1}},{0xD1,{"pop DE",true,1}},{0xD2,{"jp NC, {:#x}{:x}",true,3}},
					{0xD4,{"call NC, {:#x}{:x}",true,3}},{0xD5,{"push DE",true,1}},{0xD6,{"sub A, {:#x}",false,2}},{0xD7,{"rst 0x10",false,1}},
					{0xD8,{"ret C",false,1}},{0xD9,{"reti",false,1}},{0xDA,{"jp C, {:#x}{:x}",true,3}},                
					{0xDC,{"call C, {:#x}{:x}",true,3}},                             {0xEE,{"sbc A, {:#x}",false,2}},{0xDF,{"rst 0x18",false,1}},
					{0xE0,{"ld [FF00+{:#x}], A",false,2}},{0xE1,{"pop HL",true,1}},{0xE2,{"ld [FF00+C], A",false,1}},
					                               {0xE5,{"push HL",true,1}},{0xE6,{"and A, {:#x}",false,2}},{0xE7,{"rst 0x20",false,1}},
					{0xE8,{"add SP, {:#x}",true,2,true}},{0xE9,{"jp HL",true,1}},{0xEA,{"ld [{:#x}{:x}], A",true,3}},                
					                                                                 {0xEE,{"xor A, {:#x}",false,2}},{0xEF,{"rst 0x28",false,1}},
					{0xF0,{"ld A, [FF00+{:#x}]",false,2}},{0xF1,{"pop AF",true,1}},{0xF2,{"ld A, [FF00+C]",false,1}},{0xF3,{"DI",false,1}},
					                               {0xF5,{"push AF",true,1}},{0xF6,{"or A, {:#x}",false,2}},{0xF7,{"rst 0x30",false,1}},
					{0xF8,{"ld HL, SP+{:#x}",true,2,true}},{0xF9,{"ld SP, HL",true,1}},{0xFA,{"ld A, [{:#x}{:x}]",true,3}},{0xFB,{"EI",false,1}},                
					                                                                 {0xFE,{"cp A, {:#x}",false,2}},{0xFF,{"rst 0x38",false,1}}};

	std::map<int,std::string> cbprefix{{0x00,"rlc B"},{0x01,"rlc C"},{0x02,"rlc D"},{0x03,"rlc E"},{0x04,"rlc H"},{0x05,"rlc L"},{0x06,"rlc [HL]"},{0x07,"rlc A"},
					{0x08,"rrc B"},{0x09,"rrc C"},{0x0A,"rrc D"},{0x0B,"rrc E"},{0x0C,"rrc H"},{0x0D,"rrc L"},{0x0E,"rrc [HL]"},{0x0F,"rrc A"},
					{0x10,"rl B"},{0x11,"rl C"},{0x12,"rl D"},{0x13,"rl E"},{0x14,"rl H"},{0x15,"rl L"},{0x16,"rl [HL]"},{0x17,"rl A"},
					{0x18,"rr B"},{0x19,"rr C"},{0x1A,"rr D"},{0x1B,"rr E"},{0x1C,"rr H"},{0x1D,"rr L"},{0x1E,"rr [HL]"},{0x1F,"rr A"},
					{0x20,"sla B"},{0x21,"sla C"},{0x22,"sla D"},{0x23,"sla E"},{0x24,"sla H"},{0x25,"sla L"},{0x26,"sla [HL]"},{0x27,"sla A"},
					{0x28,"sra B"},{0x29,"sra C"},{0x2A,"sra D"},{0x2B,"sra E"},{0x2C,"sra H"},{0x2D,"sra L"},{0x2E,"sra [HL]"},{0x2F,"sra A"},
					{0x30,"swap B"},{0x31,"swap C"},{0x32,"swap D"},{0x33,"swap E"},{0x34,"swap H"},{0x35,"swap L"},{0x36,"swap [HL]"},{0x37,"swap A"},
					{0x38,"srl B"},{0x39,"srl C"},{0x3A,"srl D"},{0x3B,"srl E"},{0x3C,"srl H"},{0x3D,"srl L"},{0x3E,"srl [HL]"},{0x3F,"srl A"},
					{0x40,"bit 0, B"},{0x41,"bit 0, C"},{0x42,"bit 0, D"},{0x43,"bit 0, E"},{0x44,"bit 0, H"},{0x45,"bit 0, L"},{0x46,"bit 0, [HL]"},{0x47,"bit 0, A"},
					{0x48,"bit 1, B"},{0x49,"bit 1, C"},{0x4A,"bit 1, D"},{0x4B,"bit 1, E"},{0x4C,"bit 1, H"},{0x4D,"bit 1, L"},{0x4E,"bit 1, [HL]"},{0x4F,"bit 1, A"},
					{0x50,"bit 2, B"},{0x51,"bit 2, C"},{0x52,"bit 2, D"},{0x53,"bit 2, E"},{0x54,"bit 2, H"},{0x55,"bit 2, L"},{0x56,"bit 2, [HL]"},{0x57,"bit 2, A"},
					{0x58,"bit 3, B"},{0x59,"bit 3, C"},{0x5A,"bit 3, D"},{0x5B,"bit 3, E"},{0x5C,"bit 3, H"},{0x5D,"bit 3, L"},{0x5E,"bit 3, [HL]"},{0x5F,"bit 3, A"},
					{0x60,"bit 4, B"},{0x61,"bit 4, C"},{0x62,"bit 4, D"},{0x63,"bit 4, E"},{0x64,"bit 4, H"},{0x65,"bit 4, L"},{0x66,"bit 4, [HL]"},{0x67,"bit 4, A"},
					{0x68,"bit 5, B"},{0x69,"bit 5, C"},{0x6A,"bit 5, D"},{0x6B,"bit 5, E"},{0x6C,"bit 5, H"},{0x6D,"bit 5, L"},{0x6E,"bit 5, [HL]"},{0x6F,"bit 5, A"},
					{0x70,"bit 6, B"},{0x71,"bit 6, C"},{0x72,"bit 6, D"},{0x73,"bit 6, E"},{0x74,"bit 6, H"},{0x75,"bit 6, L"},{0x76,"bit 6, [HL]"},{0x77,"bit 6, A"},
					{0x78,"bit 7, B"},{0x79,"bit 7, C"},{0x7A,"bit 7, D"},{0x7B,"bit 7, E"},{0x7C,"bit 7, H"},{0x7D,"bit 7, L"},{0x7E,"bit 7, [HL]"},{0x7F,"bit 7, A"},
					{0x80,"res 0, B"},{0x81,"res 0, C"},{0x82,"res 0, D"},{0x83,"res 0, E"},{0x84,"res 0, H"},{0x85,"res 0, L"},{0x86,"res 0, [HL]"},{0x87,"res 0, A"},
					{0x88,"res 1, B"},{0x89,"res 1, C"},{0x8A,"res 1, D"},{0x8B,"res 1, E"},{0x8C,"res 1, H"},{0x8D,"res 1, L"},{0x8E,"res 1, [HL]"},{0x8F,"res 1, A"},
					{0x90,"res 2, B"},{0x91,"res 2, C"},{0x92,"res 2, D"},{0x93,"res 2, E"},{0x94,"res 2, H"},{0x95,"res 2, L"},{0x96,"res 2, [HL]"},{0x97,"res 2, A"},
					{0x98,"res 3, B"},{0x99,"res 3, C"},{0x9A,"res 3, D"},{0x9B,"res 3, E"},{0x9C,"res 3, H"},{0x9D,"res 3, L"},{0x9E,"res 3, [HL]"},{0x9F,"res 3, A"},
					{0xA0,"res 4, B"},{0xA1,"res 4, C"},{0xA2,"res 4, D"},{0xA3,"res 4, E"},{0xA4,"res 4, H"},{0xA5,"res 4, L"},{0xA6,"res 4, [HL]"},{0xA7,"res 4, A"},
					{0xA8,"res 5, B"},{0xA9,"res 5, C"},{0xAA,"res 5, D"},{0xAB,"res 5, E"},{0xAC,"res 5, H"},{0xAD,"res 5, L"},{0xAE,"res 5, [HL]"},{0xAF,"res 5, A"},
					{0xB0,"res 6, B"},{0xB1,"res 6, C"},{0xB2,"res 6, D"},{0xB3,"res 6, E"},{0xB4,"res 6, H"},{0xB5,"res 6, L"},{0xB6,"res 6, [HL]"},{0xB7,"res 6, A"},
					{0xB8,"res 7, B"},{0xB9,"res 7, C"},{0xBA,"res 7, D"},{0xBB,"res 7, E"},{0xBC,"res 7, H"},{0xBD,"res 7, L"},{0xBE,"res 7, [HL]"},{0xBF,"res 7, A"},
					{0xC0,"set 0, B"},{0xC1,"set 0, C"},{0xC2,"set 0, D"},{0xC3,"set 0, E"},{0xC4,"set 0, H"},{0xC5,"set 0, L"},{0xC6,"set 0, [HL]"},{0xC7,"set 0, A"},
					{0xC8,"set 1, B"},{0xC9,"set 1, C"},{0xCA,"set 1, D"},{0xCB,"set 1, E"},{0xCC,"set 1, H"},{0xCD,"set 1, L"},{0xCE,"set 1, [HL]"},{0xCF,"set 1, A"},
					{0xD0,"set 2, B"},{0xD1,"set 2, C"},{0xD2,"set 2, D"},{0xD3,"set 2, E"},{0xD4,"set 2, H"},{0xD5,"set 2, L"},{0xD6,"set 2, [HL]"},{0xD7,"set 2, A"},
					{0xD8,"set 3, B"},{0xD9,"set 3, C"},{0xDA,"set 3, D"},{0xDB,"set 3, E"},{0xDC,"set 3, H"},{0xDD,"set 3, L"},{0xDE,"set 3, [HL]"},{0xDF,"set 3, A"},
					{0xE0,"set 4, B"},{0xE1,"set 4, C"},{0xE2,"set 4, D"},{0xE3,"set 4, E"},{0xE4,"set 4, H"},{0xE5,"set 4, L"},{0xE6,"set 4, [HL]"},{0xE7,"set 4, A"},
					{0xE8,"set 5, B"},{0xE9,"set 5, C"},{0xEA,"set 5, D"},{0xEB,"set 5, E"},{0xEC,"set 5, H"},{0xED,"set 5, L"},{0xEE,"set 5, [HL]"},{0xEF,"set 5, A"},
					{0xF0,"set 6, B"},{0xF1,"set 6, C"},{0xF2,"set 6, D"},{0xF3,"set 6, E"},{0xF4,"set 6, H"},{0xF5,"set 6, L"},{0xF6,"set 6, [HL]"},{0xF7,"set 6, A"},
					{0xF8,"set 7, B"},{0xF9,"set 7, C"},{0xFA,"set 7, D"},{0xFB,"set 7, E"},{0xFC,"set 7, H"},{0xFD,"set 7, L"},{0xFE,"set 7, [HL]"},{0xFF,"set 7, A"}};



	while (1)
	{
		std::cout << std::format("{:#x}: ",pc);
		auto iter = asmtable.find(std::to_integer<int>(hexdata[pc]));
		if (iter != asmtable.end())
		{
			auto instruction = iter->second;
			std::string_view mnemonic = instruction.mnemonic;
			if (instruction.instr_size == 1)
			{
				std::cout << mnemonic << std::endl;
				pc += instruction.instr_size;
				continue;
			}
			if ((instruction.instr_size == 2) && (instruction.is_signed == false))
			{
				std::cout << std::vformat(mnemonic,std::make_format_args(std::to_integer<int>(hexdata[pc+1]))) << std::endl;
				pc += instruction.instr_size;
				continue;
			}
			if ((instruction.instr_size == 2) && (instruction.is_signed == true))
			{
				std::cout << std::vformat(mnemonic,std::make_format_args(std::to_integer<int8_t>(hexdata[pc+1]))) << std::endl;
				pc += instruction.instr_size;
				continue;
			}
			if (instruction.instr_size == 3)
			{
				std::cout << std::vformat(mnemonic,std::make_format_args(std::to_integer<int>(hexdata[pc+2]),std::to_integer<int>(hexdata[pc+1]))) << std::endl;
				pc += instruction.instr_size;
				continue;
			}
		}
		else
		{
			if (std::to_integer<int>(hexdata[pc]) == 0xCB)
			{
				auto cb_iter = cbprefix.find(std::to_integer<int>(hexdata[pc+1]));
				auto cb_mnemonic = cb_iter->second;
				std::cout << cb_mnemonic << std::endl;
				pc +=2;
				continue;
			}
			else
			{
				std::cout << "Unknown instruction\n";
				pc += 1;
			}
		}	
	}
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
	gbdisasm(gbinfo(hexdata),hexdata);

	return 0;

}
