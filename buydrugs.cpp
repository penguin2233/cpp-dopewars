#include <iostream>
#include <thread>
#include "buydrugs.h"
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
extern bool dlc;

void buyweed()
{
	std::cout << "how much weed do you want to buy? enter amount then press enter" << '\n';
	int weedpurchaseamount;
	std::cin >> weedpurchaseamount;
	int weedpurchasetotal = weedpurchaseamount * weedprice;
	std::cout << "your total is $" << weedpurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
	char purchase;
	std::cin >> purchase;
	switch (purchase)
	{
	case 'y':
		if (money > weedpurchasetotal)
		{
			money = money - weedpurchasetotal;
			weedpocket = weedpocket + weedpurchaseamount;
			clearscreen();
		}
		else if (money < weedpurchasetotal)
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
}

void buycocaine()
{
	std::cout << "how much cocaine do you want to buy? enter amount then press enter" << '\n';
	int cocainepurchaseamount;
	std::cin >> cocainepurchaseamount;
	int cocainepurchasetotal = cocainepurchaseamount * cocaineprice;
	std::cout << "your total is $" << cocainepurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
	char purchase;
	std::cin >> purchase;
	switch (purchase)
	{
	case 'y':
		if (money > cocainepurchasetotal)
		{
			money = money - cocainepurchasetotal;
			cocainepocket = cocainepocket + cocainepurchaseamount;
			clearscreen();
		}
		else if (money < cocainepurchasetotal)
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
}

void buyacid()
{
	std::cout << "how much acid do you want to buy? enter amount then press enter" << '\n';
	int acidpurchaseamount;
	std::cin >> acidpurchaseamount;
	int acidpurchasetotal = acidpurchaseamount * acidprice;
	std::cout << "your total is $" << acidpurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
	char purchase;
	std::cin >> purchase;
	switch (purchase)
	{
	case 'y':
		if (money > acidpurchasetotal)
		{
			money = money - acidpurchasetotal;
			acidpocket = acidpocket + acidpurchaseamount;
			clearscreen();
		}
		else if (money < acidpurchasetotal)
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
}

void buylsd()
{
	std::cout << "how much lsd do you want to buy? enter amount then press enter" << '\n';
	int lsdpurchaseamount;
	std::cin >> lsdpurchaseamount;
	int lsdpurchasetotal = lsdpurchaseamount * lsdprice;
	std::cout << "your total is $" << lsdpurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
	char purchase;
	std::cin >> purchase;
	switch (purchase)
	{
	case 'y':
		if (money > lsdpurchasetotal)
		{
			money = money - lsdpurchasetotal;
			lsdpocket = lsdpocket + lsdpurchaseamount;
			clearscreen();
		}
		else if (money < lsdpurchasetotal)
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
}

void buycondoms()
{
	std::cout << "how many condoms do you want to buy? enter amount then press enter" << '\n';
	int condompurchaseamount;
	std::cin >> condompurchaseamount;
	int condompurchasetotal = condompurchaseamount * condomprice;
	std::cout << "your total is $" << condompurchasetotal << " do you want to buy? y for yes, n for no" << '\n';
	char purchase;
	std::cin >> purchase;
	switch (purchase)
	{
	case 'y':
		if (money > condompurchasetotal)
		{
			money = money - condompurchasetotal;
			condompocket = condompocket + condompurchaseamount;
			clearscreen();
		}
		else if (money < condompurchasetotal)
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
}