#include <iostream>
#include <thread>
#include "selldrugs.h"
#include "clearscreen.h"

extern float money;
extern int weedprice;
extern int cocaineprice;
extern int acidprice;
extern int lsdprice;
extern int condomprice;
extern int weedpocket;
extern int cocainepocket;
extern int acidpocket;
extern int lsdpocket;
extern int condompocket;

void sellweed()
{
	std::cout << "how much weed do you want to sell? enter amount then press enter" << '\n';
	int weedsellamount;
	std::cin >> weedsellamount;
	int weedselltotal = weedsellamount * weedprice;
	std::cout << "your total is $" << weedselltotal << " do you want to sell? y for yes, n for no" << '\n';
	char sell;
	std::cin >> sell;
	switch (sell)
	{
	case 'y':
		if (weedpocket >= weedsellamount)
		{
			money = money + weedselltotal;
			weedpocket = weedpocket - weedsellamount;
			clearscreen();
		}
		else if (weedpocket < weedsellamount)
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

void sellcocaine()
{
	std::cout << "how much cocaine do you want to sell? enter amount then press enter" << '\n';
	int cocainesellamount;
	std::cin >> cocainesellamount;
	int cocaineselltotal = cocainesellamount * cocaineprice;
	std::cout << "your total is $" << cocaineselltotal << " do you want to sell? y for yes, n for no" << '\n';
	char sell;
	std::cin >> sell;
	switch (sell)
	{
	case 'y':
		if (cocainepocket >= cocainesellamount)
		{
			money = money + cocaineselltotal;
			cocainepocket = cocainepocket - cocainesellamount;
			clearscreen();
		}
		else if (cocainepocket < cocainesellamount)
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

void sellacid()
{
	std::cout << "how much acid do you want to sell? enter amount then press enter" << '\n';
	int acidsellamount;
	std::cin >> acidsellamount;
	int acidselltotal = acidsellamount * acidprice;
	std::cout << "your total is $" << acidselltotal << " do you want to sell? y for yes, n for no" << '\n';
	char sell;
	std::cin >> sell;
	switch (sell)
	{
	case 'y':
		if (acidpocket >= acidselltotal)
		{
			money = money + acidselltotal;
			acidpocket = acidpocket - acidsellamount;
			clearscreen();
		}
		else if (acidpocket < acidsellamount)
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

void selllsd()
{
	std::cout << "how much lsd do you want to sell? enter amount then press enter" << '\n';
	int lsdsellamount;
	std::cin >> lsdsellamount;
	int lsdselltotal = lsdsellamount * lsdprice;
	std::cout << "your total is $" << lsdselltotal << " do you want to sell? y for yes, n for no" << '\n';
	char sell;
	std::cin >> sell;
	switch (sell)
	{
	case 'y':
		if (lsdpocket >= lsdsellamount)
		{
			money = money + lsdselltotal;
			lsdpocket = lsdpocket - lsdsellamount;
			clearscreen();
		}
		else if (lsdpocket < lsdsellamount)
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

void sellcondoms()
{
	std::cout << "how many condoms do you want to sell? enter amount then press enter" << '\n';
	int condomsellamount;
	std::cin >> condomsellamount;
	int condomselltotal = condomsellamount * condomprice;
	std::cout << "your total is $" << condomselltotal << " do you want to sell? y for yes, n for no" << '\n';
	char sell;
	std::cin >> sell;
	switch (sell)
	{
	case 'y':
		if (condompocket >= condomsellamount)
		{
			money = money + condomselltotal;
			condompocket = condompocket - condomsellamount;
			clearscreen();
		}
		else if (condompocket < condomsellamount)
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