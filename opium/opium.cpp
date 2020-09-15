#include "pch.h"
#include "opium.h"
#include <random>
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <cpr/cpr.h>
#include <Windows.h>
#include <boost/exception/all.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

// if you wanted to ever make your own DLC, edit the values here
std::string dlcName = "Opium Expansion v1.1";
std::string key = "420"; // simple anti piracy check attempt (too easy to bypass smh)
std::string authServer = "https://penguin2233.gq/projects/cpp-dopewars/key.php"; // key checking server, more info on github
int raidAdd = 5000;
int randomRange1 = 1000;
int randomRange2 = 10000;

__declspec(dllimport) extern std::string name;
__declspec(dllimport) extern float money;
__declspec(dllimport) extern int debt;
__declspec(dllimport) extern int days;
__declspec(dllimport) extern int weedpocket;
__declspec(dllimport) extern int cocainepocket;
__declspec(dllimport) extern int acidpocket;
__declspec(dllimport) extern int lsdpocket;
__declspec(dllimport) extern int condompocket;
__declspec(dllimport) extern int dlcPrice;
__declspec(dllimport) extern int dlcPocket;
__declspec(dllimport) extern std::string dlcDrugName;
__declspec(dllimport) extern std::string dlcDrugLetter;
__declspec(dllimport) extern std::mt19937 eng;

bool antiPiracy() {
	std::cout << "checking serial key (" << key << ")" << '\n';
	cpr::Response keyCheckRequest = cpr::Get(cpr::Url{ authServer },
		cpr::Parameters{ {"key", key} });
	if (keyCheckRequest.status_code == 420)
	{
		return true;
	}
	if (keyCheckRequest.status_code == 402)
	{
		return false;
	}
	if (keyCheckRequest.status_code != 420 && keyCheckRequest.status_code != 402)
	{
		std::cout << "failed to verify dlc key because of server error (EA games moment) \n";
		return false;
	}
}

void clearscreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void sell2() {
	std::cout << "sell opium (o) or anything else to exit \n";
	char sell2menu;
	std::cin >> sell2menu;
	switch (sell2menu) {
	case 'o':
	{
		std::cout << "how much opium do you want to sell? enter amount then press enter" << '\n';
		int opiumsellamount;
		std::cin >> opiumsellamount;
		int opiumselltotal = opiumsellamount * dlcPrice;
		std::cout << "your total is $" << opiumselltotal << " do you want to sell? y for yes, n for no" << '\n';
		char sell;
		std::cin >> sell;
		switch (sell)
		{
		case 'y':
			if (dlcPocket >= opiumsellamount)
			{
				money = money + opiumselltotal;
				dlcPocket = dlcPocket - opiumsellamount;
				clearscreen();
			}
			else if (dlcPocket < opiumsellamount)
			{
				std::cout << "not enough drugs :(" << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				clearscreen();
			}
			break;
		case 'n':
			clearscreen();
			break;
		default:
			std::cout << "invalid choice." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			clearscreen();
			break;
		}
	}
	default:
		break;
	}
	return;
}

void buy2() {
	std::cout << "buy opium (o) or anything else to exit \n";
	char buy2menu;
	std::cin >> buy2menu;
	switch (buy2menu) {
	case 'o':
	{
		std::cout << "how many opium do you want to buy? enter amount then press enter" << '\n';
		int opiumpurchaseamount;
		std::cin >> opiumpurchaseamount;
		int opiumpurchasetotal = opiumpurchaseamount * dlcPrice;
		std::cout << "your total is $" << opiumpurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
		char purchase;
		std::cin >> purchase;
		switch (purchase)
		{
		case 'y':
			if (money > opiumpurchasetotal)
			{
				money = money - opiumpurchasetotal;
				dlcPocket = dlcPocket + opiumpurchaseamount;
				clearscreen();
			}
			else if (money < opiumpurchasetotal)
			{
				std::cout << "not enough money :(" << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				clearscreen();
			}
			break;
		case 'n':
			clearscreen();
			break;
		default:
			std::cout << "invalid choice." << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			clearscreen();
			break;
		}
		return;
		break;
	}
	default:
		break;
	}		
	return;
}

int save() {
	std::cout << "dlc aware-ish save function (c) penguin2233 2020" << '\n';
	try {
		boost::property_tree::ptree savefile;

		savefile.put("money.money", money);
		savefile.put("money.debt", debt);

		savefile.put("days.days", days);

		savefile.put("drugs.weed", weedpocket);
		savefile.put("drugs.cocaine", cocainepocket);
		savefile.put("drugs.acid", acidpocket);
		savefile.put("drugs.lsd", lsdpocket);
		savefile.put("drugs.condom", condompocket);
		savefile.put("drugs.opium", dlcPocket);

		savefile.put("dlc.dlc", "1");

		write_ini(name + ".sav", savefile);
		return 200;
	}
	catch (boost::exception &e) {
		std::cout << '\n' << "saving failed \n";
		return 201;
	}	
}

int load() {
	std::cout << "dlc aware-ish load function (c) penguin2233 2020" << '\n';
	boost::property_tree::ptree loadfile;

	try {
		boost::property_tree::read_ini(name + ".sav", loadfile);
	}
	catch (boost::exception &e) {
		std::cout << "save file " << name << ".sav does not exist" << '\n';
		return 201;
	}

	try {
		int dlcAware = loadfile.get<int>("dlc.dlc");
		if (dlcAware == 1)
		{
			money = loadfile.get<float>("money.money");
			debt = loadfile.get<float>("money.debt");

			days = loadfile.get<int>("days.days");

			weedpocket = loadfile.get<int>("drugs.weed");
			cocainepocket = loadfile.get<int>("drugs.cocaine");
			acidpocket = loadfile.get<int>("drugs.acid");
			lsdpocket = loadfile.get<int>("drugs.lsd");
			condompocket = loadfile.get<int>("drugs.condom");

			dlcPocket = loadfile.get<int>("drugs.opium");
			return 200;
		}
		else throw;
	}
	catch (boost::exception &e){
		std::cout << '\n' << "save file is not compatible with this DLC \n";
		return 201;
	}
}

void loadDLC() {
	std::cout << "loading " << dlcName << "\n";
	dlcDrugName = "Opium";
	dlcDrugLetter = 'o';
	return;
}

int dlcMagic(int h)
{
	switch (h) {
	case 1: // check key and setup dlc variables
		if (antiPiracy() == TRUE)
		{
			loadDLC();
		}
		else
		{
			system("color 1f");
			std::cout << "the anti piracy check failed \n";
			system("color");
			return 202;
		}
		break;
	case 2: // dlc info string
		std::cout << dlcName <<'\n';
		break;
	case 3: // dlc aware-ish load 
		if (load() == 201)
			return 201;
		else if (load() == 200)
			return 0;
	case 4: // dlc aware-ish save
		if (save() == 201)
			return 201;
		else if (save() == 200)
			return 0;
	case 5: // dlc aware-ish buy2 menu
		buy2();
		break;
	case 6: // dlc aware-ish sell2 menu
		sell2(); 
		break;
	case 8: // make prices
	{
		std::uniform_int_distribution<> opiumpricerange(randomRange1, randomRange2);
		dlcPrice = opiumpricerange(eng);
		break;
	}		
	case 9: // raid pricing
		dlcPrice = dlcPrice + raidAdd;
		break;
	default: // just in case to prevent unknown progam behaviour
		system("color 1f");
		std::cout << "internal program error, stopping execution to prevent damage \n";
		system("color");
		return 203;
	}
	return 0;
}