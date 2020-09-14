#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "saveandload.h"

using namespace boost::property_tree;

extern std::string name;
extern float money;
extern int debt;
extern int days;
extern int weedpocket;
extern int cocainepocket;
extern int acidpocket;
extern int lsdpocket;
extern int condompocket;

void savetofile()
{
	std::cout << "beta feature in testing..." << '\n';
	ptree savefile;

	savefile.put("money.money", money);
	savefile.put("money.debt", debt);

	savefile.put("days.days", days);

	savefile.put("drugs.weed", weedpocket);
	savefile.put("drugs.cocaine", cocainepocket);
	savefile.put("drugs.acid", acidpocket);
	savefile.put("drugs.lsd", lsdpocket);
	savefile.put("drugs.condom", condompocket);

	write_ini(name + ".sav", savefile);
	return;
}

void loadfromfile()
{
	std::cout << "feature in testing" << '\n';
	ptree loadfile;

	read_ini(name + ".sav", loadfile);

	money = loadfile.get<float>("money.money");
	debt = loadfile.get<float>("money.debt");

	days = loadfile.get<int>("days.days");

	weedpocket = loadfile.get<int>("drugs.weed");
	cocainepocket = loadfile.get<int>("drugs.cocaine");
	acidpocket = loadfile.get<int>("drugs.acid");
	lsdpocket = loadfile.get<int>("drugs.lsd");
	condompocket = loadfile.get<int>("drugs.condom");

	return;
}
