// I hate this, might rewrite in future

#include <iostream>
#include <bass.h>
#include <thread>
#include <future>
#include <string>
#include <Windows.h>
#include <random>
#include <iomanip>
#include <cmath>
#include <boost/filesystem.hpp>
#include "clearscreen.h"
#include "saveandload.h"
#include "buydrugs.h"
#include "selldrugs.h"

// global code yes i know plz dont kill me >.<
typedef void(__cdecl* MYPROC)(int);
HINSTANCE hinstLib;
MYPROC dlcMagic;
BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

// dll exporting lmao
__declspec(dllexport) std::string name;
bool globalexit = FALSE;
bool musicon = TRUE;
bool gameprestart = FALSE;
bool gamestarted = FALSE;
__declspec(dllexport) float money = 1000;
__declspec(dllexport) int debt = 1000;
__declspec(dllexport) int days = 0;
int weedprice;
int cocaineprice;
int acidprice;
int lsdprice;
int condomprice;
int raid;
__declspec(dllexport) int weedpocket = 0;
__declspec(dllexport) int cocainepocket = 0;
__declspec(dllexport) int acidpocket = 0;
__declspec(dllexport) int lsdpocket = 0;
__declspec(dllexport) int condompocket = 0;
int cheatused = 0;
bool dlc = FALSE;
__declspec(dllexport) int dlcPocket;
__declspec(dllexport) int dlcPrice;
__declspec(dllexport) std::string dlcDrugName;
__declspec(dllexport) std::string dlcDrugLetter;
__declspec(dllexport) std::random_device rd;
__declspec(dllexport) std::mt19937 eng(rd());

void dubstep()
{
	BASS_Free();
	BASS_Init(-1, 48000, 0, 0, 0);
	HSTREAM stream = BASS_StreamCreateFile(FALSE, "resource.bin", 0, 0, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(stream, true);
	while (true)
		
		if (globalexit == TRUE)
		{
			return;
		}
		else if (musicon == TRUE)
		{
			DWORD playing = BASS_ChannelIsActive(stream);
			if (playing == BASS_ACTIVE_PAUSED)
			{
				BASS_ChannelPlay(stream, true);
			}
			else
				std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else if (musicon == FALSE)
		{
			BASS_ChannelPause(stream);
		}


}

void makedrugprice()
{
	std::uniform_int_distribution<> weedpricerange(230, 700);
	weedprice = weedpricerange(eng);
	// std::cout << weedprice << '\n';

	std::uniform_int_distribution<> cocainepricerange(8000, 18000);
	cocaineprice = cocainepricerange(eng);
	// std::cout << cocaineprice << '\n';

	std::uniform_int_distribution<> acidpricerange(700, 3000);
	acidprice = acidpricerange(eng);
	// std::cout << acidprice << '\n';

	std::uniform_int_distribution<> lsdpricerange(2500, 3500);
	lsdprice = lsdpricerange(eng);
	// std::cout << lsdprice << '\n';

	std::uniform_int_distribution<> condompricerange(7, 50);
	condomprice = condompricerange(eng);
	// std::cout << condomprice << '\n';

	std::uniform_int_distribution<> raidchance(1, 100);
	raid = raidchance(eng);

	if (dlc == TRUE)
	{
		dlcMagic(8);
	}
	if (raid == 1 && days != 1)
	{
		weedprice = weedprice + 300;
		cocaineprice = cocaineprice + 3200;
		acidprice = acidprice + 600;
		lsdprice = lsdprice + 2000;
		if (dlc == TRUE)
		{
			dlcMagic(9);
		}
		std::cout << "holy shit a police raid, prices have gone through the roof" << '\n';
	}

	return;
}

void nextday()
{
	clearscreen();
	if (debt < 0)
	{
		debt = 0;
	}
	if (debt != 0)
	{
		debt = debt*pow((1+0.01),days);
	}
	days++;
	makedrugprice();
	return;
}

void payloan()
{
	clearscreen();
	if (debt == 0)
	{
		std::cout << "you dont have a loan to pay!" << '\n';
		return;
	}
	else
	{
		std::cout << "how much of your loan do you want to pay? \nyou owe $" << debt << " and you have $" << money << '\n';
		int loanpay;
		std::cin >> loanpay;
		if (loanpay > money)
		{
			std::cout << "you dont have enough money" << '\n';
			return;
		}
		if (loanpay <= money)
		{
			std::cout << "you will have a debt of $" << debt - loanpay << " and you will have $" << money - loanpay << " in cash" << '\n' << '\n';
			std::cout << "do you want to pay off your debt? y for yes, n for no" << '\n';
			char loanpayconfirm;
			std::cin >> loanpayconfirm;
			switch (loanpayconfirm)
			{
			case 'y':
				clearscreen();
				debt = debt - loanpay;
				money = money - loanpay;
				break;
			case 'n':
				clearscreen();
				break;
			default:
				clearscreen();
				std::cout << "invalid option" <<'\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				break;
			}
		}
		return;
	}
}

void sellmenu2()
{
	std::cout << "okay, which drug would you like to sell? type in the drug initial then press enter." << '\n';
	if (dlc == TRUE)
	{
		std::cout << "type d for the dlc menu (yeah it sucks idk how to do this better unless i rewrite the whole thing \n";
	}
	char sellmenu2;
	std::cin >> sellmenu2;
	switch (sellmenu2)
	{
	case 'w':
		sellweed();
		break;
	case 'c':
		sellcocaine();
		break;
	case 'a':
		sellacid();
		break;
	case 'l':
		selllsd();
		break;
	case 'C':
		sellcondoms();
		break;
	case 'd':
		if (dlc == TRUE)
			dlcMagic(6);
		else {
			std::cout << "no dlc \n";
			break;
		}
	default:
		std::cout << "invalid drug name. make sure you type in the initial letter of the drug then press enter. cocaine is c and condoms are C" << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(2));
		break;
	}
	return;
}

void sellmenu1()
{
	clearscreen();
	bool selling = TRUE;
	while (selling == TRUE)
	{
		std::cout << "welcome to the sell menu. you have $" << money << '\n' << '\n';
		std::cout << "current drugs in your pockets" << '\n';
		std::cout << "weed: " << weedpocket << '\n';
		std::cout << "cocaine: " << cocainepocket << '\n';
		std::cout << "acid: " << acidpocket << '\n';
		std::cout << "lsd: " << lsdpocket << '\n';
		std::cout << "Condoms: " << condompocket << '\n';
		if (dlc == TRUE)
		{
			std::cout << dlcDrugName << ":" << dlcPocket << '\n \n';
		}
		else std::cout << '\n';
		std::cout << "current drug prices" << '\n';
		if (raid == 1)
			std::cout << "there has been a police raid, prices are increased" << '\n';
		std::cout << "weed: $" << weedprice << '\n';
		std::cout << "cocaine: $" << cocaineprice << '\n';
		std::cout << "acid: $" << acidprice << '\n';
		std::cout << "lsd: $" << lsdprice << '\n';
		std::cout << "Condoms: " << condomprice << '\n';
		if (dlc == TRUE)
		{
			std::cout << dlcDrugName << ":" << dlcPrice << '\n \n';
		}
		else std::cout << '\n';
		std::cout <<
			"s: sell some drugs \n"
			"e: exit the buy menu \n" << '\n';
		char sellmenu1;
		std::cin >> sellmenu1;
		switch (sellmenu1)
		{
		case 's':
			sellmenu2();
			break;
		case 'e':
			selling = FALSE;
			break;
		default:
			std::cout << "invalid option" << '\n';
			break;
		}
	}
	clearscreen();
	return;
}

void buymenu2()
{
	std::cout << "okay, which drug would you like to buy? type in the drug initial then press enter." << '\n';
	if (dlc == TRUE)
	{
		std::cout << "type d for the dlc menu (yeah it sucks idk how to do this better unless i rewrite the whole thing \n";
	}
	else {
		char buymenu2;
		std::cin >> buymenu2;
		switch (buymenu2)
		{
		case 'w':
			buyweed();
			break;
		case 'c':
			buycocaine();
			break;
		case 'a':
			buyacid();
			break;
		case 'l':
			buylsd();
			break;
		case 'C':
			buycondoms();
			break;
		case 'd':
			if (dlc == TRUE)
				dlcMagic(5);
			else {
				std::cout << "no dlc \n";
				break;
			}
		default:
			std::cout << "invalid drug name. make sure you type in the initial letter of the drug then press enter. cocaine is c and condoms are C" << '\n';
			std::this_thread::sleep_for(std::chrono::seconds(2));
			break;
		}
	}

	return;
}

void buymenu1()
{
	clearscreen();
	bool buying = TRUE;
	while (buying == TRUE)
	{
		std::cout << "welcome to the buy menu. you have $" << money << '\n' << '\n';
		std::cout << "current drugs in your pockets" << '\n';
		std::cout << "weed: " << weedpocket << '\n';
		std::cout << "cocaine: " << cocainepocket << '\n';
		std::cout << "acid: " << acidpocket << '\n';
		std::cout << "lsd: " << lsdpocket << '\n';
		std::cout << "Condoms: " << condompocket << '\n';
		if (dlc == TRUE)
		{
			std::cout << dlcDrugName << ":" << dlcPocket << '\n \n';
		}
		else std::cout << '\n';
		std::cout << "current drug prices" << '\n';
		if (raid == 1)
			std::cout << "there has been a police raid, prices are increased" << '\n';
		std::cout << "weed: $" << weedprice << '\n';
		std::cout << "cocaine: $" << cocaineprice << '\n';
		std::cout << "acid: $" << acidprice << '\n';
		std::cout << "lsd: $" << lsdprice << '\n';
		std::cout << "Condoms: " << condomprice << '\n';
		if (dlc == TRUE)
		{
			std::cout << dlcDrugName << ":" << dlcPrice << '\n \n';
		}
		else std::cout << '\n';
		std::cout <<
			"b: buy some drugs \n"
			"e: exit the buy menu \n" << '\n';
		char buymenu1;
		std::cin >> buymenu1;
		switch (buymenu1)
		{
		case 'b':
			buymenu2();
			break;
		case 'e':
			buying = FALSE;
			break;
		default:
			std::cout << "invalid option" << '\n';
			break;
		}
	}
	clearscreen();
	return;
}

int main(int argc, char** argv)
{
	// DLC checking but im lazy to seperate it
	// i also don't know what this code does or how it works :^)
	// ms dev docs ftw
	if (argc == 2) {
		std::string dlcFileName = argv[1];
		std::wstring dlcFileNameWide(dlcFileName.begin(), dlcFileName.end());
		if (boost::filesystem::exists(dlcFileName))
		{
			LPCWSTR lpcwstrLMAO = dlcFileNameWide.c_str();
			hinstLib = LoadLibrary(lpcwstrLMAO);
			if (hinstLib != NULL)
			{
				dlcMagic = (MYPROC)GetProcAddress(hinstLib, "?dlcMagic@@YAXH@Z");
				if (dlcMagic == NULL)
				{
					std::cout << GetLastError();
					std::cout << "fuck, loading DLC failed (function not located in DLL) \n";
				}
				if (NULL != dlcMagic)
				{
					std::cout << "we have successfully loaded function from DLL \n";
					dlcMagic(1);
				}
			}
		}
	}


	std::cout << "what is your name?" << '\n';
	std::getline(std::cin, name);
	clearscreen();
	
	auto music = std::async(std::launch::async, dubstep);

	// main menu
	if (days == 0)
	{
		bool validoption = FALSE;
		while (validoption == FALSE)
		{
			std::cout << "hi " << name << " and welcome to cpp dope wars" << '\n';
			if (dlc == TRUE)
			{
				std::cout << "you have the following DLC enabled \n";
				dlcMagic(2);
				std::cout << '\n \n';
			}
			else std::cout << '\n';
			std::cout <<
				"p: start new game \n"
				"e: exit program :( \n"
				"m: toggle music \n"
				"a: about \n"
				"make your selection then press enter \n";

			char mainmenu;
			std::cin >> mainmenu;

			switch (mainmenu)
			{
			case 'p':
				std::cout << "starting game";
				days++;
				gameprestart = TRUE;
				validoption = TRUE;
				break;
			case 'e':
				globalexit = TRUE;
				validoption = TRUE;
				break;
			case 'm':
				if (musicon == TRUE)
				{
					musicon = FALSE;
					clearscreen();
					break;
				}
				if (musicon == FALSE)
				{
					musicon = TRUE;
					clearscreen();
					break;
				}
			case 'l':
				std::cout << "attempting to load save file";
				clearscreen();
				if (dlc == TRUE)
				{
					dlcMagic(3);
				}
				else loadfromfile();				
				gameprestart = TRUE;
				validoption = TRUE;
				break;
			case 'h':
				clearscreen();
				std::cout << "help is on the way soon tm (mfw its been like 1 year and still no help)" << '\n';
				break;
			case 'a':
				std::cout << "version 6, dlc aware™" << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				clearscreen();
				break;
			default:
				clearscreen();
				std::cout << "you did not select any of the listed options, please try again" << '\n' << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				break;
			}
		}
	}


	// initialise game
	if (gameprestart == TRUE)
	{
		clearscreen();
		makedrugprice();
		gamestarted = TRUE;
	}

	// game menu
	while (gamestarted == TRUE)
	{
		{
			std::cout << "Welcome to day " << days << " of CPP Dope Wars. You owe $" << debt << " to the loan shark. You currently have $" << money << '\n';
			std::cout <<
				"b: buy menu \n"
				"v: sell menu \n"
				"p: pay off your loan (if you have one) \n"
				"n: next day \n"
				"m: toggle music \n"
				"e: exit :( \n"
				"l: load game \n"
				"s: save game \n"
				"make your selection then press enter \n";
			char gamemenu;
			std::cin >> gamemenu;

			switch (gamemenu)
			{
			case 'b':
				buymenu1();
				break;
			case 'v':
				sellmenu1();
				break;
			case 'n':
				nextday();
				break;
			case 'p':
				payloan();
				break;
			case 'e':
				globalexit = TRUE;
				gamestarted = FALSE;
				break;
			case 'm':
				if (musicon == TRUE)
				{
					musicon = FALSE;
					clearscreen();
					break;
				}
				if (musicon == FALSE)
				{
					musicon = TRUE;
					clearscreen();
					break;
				}
			case 'l':
				std::cout << "loading game progress from file..." << '\n';
				if (dlc == TRUE)
				{
					dlcMagic(3);
				}
				else loadfromfile();
				clearscreen();
				break;
			case 's':
				std::cout << "saving game progress to file..." << '\n';
				if (dlc == TRUE)
				{
					dlcMagic(4);
				}
				else savetofile();				
				clearscreen();
				break;
			case '=':
				if (cheatused < 4)
				{
					cheatused = cheatused + 1;
					money = money + 1000;
					clearscreen();
					break;
				}
				if (cheatused > 4)
				{
					clearscreen();
					break;
				}
			default:
				clearscreen();
				std::cout << "you did not select any of the listed options, please try again" << '\n';
				std::this_thread::sleep_for(std::chrono::seconds(2));
				break;
			}
		}
	}
	
	fFreeResult = FreeLibrary(hinstLib);
	return 0;
}
