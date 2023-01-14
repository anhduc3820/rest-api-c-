#include <iostream>
#include <string>
#include <spdlog/spdlog.h>
#include "Interrupt.h"
#include "Application.h"


Application::Application() 
	: m_config(nullptr), m_pgSql(nullptr)
{ }

Application::~Application()
{
	shutdown();
}

bool Application::initApp()
{
	m_config = new Config();
	if (!m_config->initConfig())
	{
		SPDLOG_ERROR("Failed read config file !");
		return false;
	}

	m_pgSql = new PgSql(m_config->getHostDb(), m_config->getPortDb(), m_config->getUserDb(), m_config->getPassDb(), m_config->getDbName());
	m_pgSql->connectPgSql();
	if (!m_pgSql->isConnect)
	{
		SPDLOG_ERROR("Failed connect database !");
		return false;
	}

	return true;
}

void Application::run()
{
	try
	{
		cfx::InterruptHandler::hookSIGINT();
		SPDLOG_INFO("APPLICATION RUN SUCCESS !");

		cfx::InterruptHandler::waitForUserInterrupt();
	}
	catch (const std::exception& err)
	{
		SPDLOG_ERROR("APPLICATION RUN FAILED {} !", err.what());
		return;
	}
}

void Application::shutdown()
{
	if (m_config)
		m_config->~Config();

	if (m_pgSql)
		m_pgSql->~PgSql();
}

void Application::getUsers()
{
	pqxx::result users = m_pgSql->query("SELECT * FROM users");
	for (size_t i = 0; i < users.size(); i++)
	{
		std::cout << "Id: " << users[i][0]
			<< "\nUsername: " << users[i][1]
			<< "\nPhone: " << users[i][2]
			<< "\nPassword: " << users[i][3]
			<< "\nEmail: " << users[i][4]
			<< "\nCreateAt: " << users[i][5]
			<< "\nActive: " << users[i][6]
			<< std::endl;
	}
}
