#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include "ini.h"
#include "Config.h"


Config::Config() 
	: m_pathConfig("./config/config.ini")
{ }

Config::Config(std::string pathFile)
	: m_pathConfig(pathFile)
{ }

Config::~Config()
{
	iniConf.clear();
}

bool Config::initConfig()
{
	try
	{
		mINI::INIFile file(m_pathConfig);
		file.read(iniConf);
		SPDLOG_INFO("INIT CONFIG FILE SUCCESS !");
		return true;
	}
	catch (const std::exception& err)
	{
		SPDLOG_INFO("INIT CONFIG FILE ERROR {} !", err.what());
		return false;
	}
}

std::string Config::getHostDb() 
{
	return iniConf.get("database").get("host");
}

std::string Config::getPortDb() 
{
	return iniConf.get("database").get("port");
}

std::string Config::getUserDb()
{
	return iniConf.get("database").get("user");
}

std::string Config::getPassDb()
{
	return iniConf.get("database").get("password");
}

std::string Config::getDbName()
{
	return iniConf.get("database").get("dbName");
}
