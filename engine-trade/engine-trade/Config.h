#ifndef Config_HEADER
#define Config_HEADER

#include <iostream>
#include <string>
#include "ini.h"


class Config
{
public:
	Config();
	Config(std::string pathFile);
	~Config();

	mINI::INIStructure iniConf;

	bool initConfig();
	std::string getHostDb();
	std::string getPortDb();
	std::string getUserDb();
	std::string getPassDb();
	std::string getDbName();

private:
	std::string m_pathConfig;
};

#endif