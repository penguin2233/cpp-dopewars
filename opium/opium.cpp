#include "pch.h"
#include "opium.h"
#include <random>
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <cpr/cpr.h>
#include <Windows.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

// if you wanted to ever make your own DLC, edit the values here
std::string dlcName = "Opium Expansion v1";
std::string key = "420"; // simple anti piracy check attempt (too easy to bypass smh)
std::string authServer = "https://penguin2233.gq/projects/cpp-dopewars/dlc.php"; // key checking server, more info on github
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
	cpr::Response keyCheckRequest = cpr::Get(cpr::Url{ authServer },
		cpr::Parameters{ {"key", key} });
	if (keyCheckRequest.status_code == 200)
	{
		return true;
	}
	if (keyCheckRequest.status_code == 420)
	{
		return false;
	}
	if (keyCheckRequest.status_code != 200 && keyCheckRequest.status_code != 420)
	{
		std::cout << "failed to verify dlc key because of server error (EA games moment) \n";
		return false;
	}
}

int panik() {
	system("color");
	return 0;
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

void save() {
	std::cout << "dlc aware-ish save function (c) penguin2233 2020" << '\n';
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

	write_ini(name + ".sav", savefile);
	return;
}

void load() {
	std::cout << "dlc aware-ish load function (c) penguin2233 2020" << '\n';
	boost::property_tree::ptree loadfile;

	read_ini(name + ".sav", loadfile);

	if (loadfile.get<int>("dlc.dlc") == 1)
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
	}
	else {
		std::cout << "this save file is incompatible with your current loaded DLCs :( \n";
		panik();
	}

	return;
}

void loadDLC() {
	std::cout << "loading" << dlcName << "\n";
	dlcDrugName = "Opium";
	dlcDrugLetter = 'o';
	return;
}

void dlcMagic(int h)
{
	switch (h) {
	case 1: // check key and """load""" dlc
		if (antiPiracy() == TRUE)
		{
			loadDLC();
		}
		else
		{
			system("color 1f");
			std::cout << "the anti piracy check failed \n";
			panik();
		}
		break;
	case 2: // dlc info string
		std::cout << dlcName <<'\n';
		break;
	case 3: // dlc aware-ish load
		load();
		break;
	case 4: // dlc aware-ish save
		save();
		break;
	case 5: // dlc aware-ish buy2 menu
		buy2();
		break;
	case 6:
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
	default:
		system("color 1f");
		std::cout << "yo dude wtf the :b: rogram called dlcMagic() but in a fucked up way. program execution stopping to prevent bruh moment \n";
		panik();
	}
	return;
}