#include <iostream>
#include <string>
#include "Config.h"
#include "PgSql.h"


class Application
{
public:
	Application();
	~Application();

	bool initApp();
	void run();
	void shutdown();

	void getUsers();

private:
	Config* m_config;
	PgSql* m_pgSql;
};