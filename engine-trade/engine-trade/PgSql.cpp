#include <iostream>
#include <windows.h>  
#include <string>
#include <format>
#include <pqxx/pqxx>
#include "PgSql.h"
#include <spdlog/spdlog.h>


PgSql::PgSql() { }

PgSql::PgSql(std::string hostPg, std::string portPg, std::string userPg, std::string passwordPg, std::string dbnamePg)
	: host(hostPg), port(portPg), user(userPg), password(passwordPg), dbname(dbnamePg) 
{ }

PgSql::~PgSql()
{
	disconectPgSql();
}

void PgSql::connectPgSql()
{
	while (!isConnect)
	{
		try
		{
			std::string connectionString = std::format("host={} port={} dbname={} user={} password ={}", host, port, dbname, user, password);
			conn_Pg = new pqxx::connection(connectionString);
			if (conn_Pg->is_open())
			{
				isConnect = true;
				SPDLOG_INFO("CONNECT DATABASE SUCCESS !");
			}

			if (!isConnect)
				SPDLOG_INFO("DISCONNECT DATABASE");
		}
		catch (const std::exception& err)
		{
			SPDLOG_ERROR("Throws ex: {}", err.what());
			isConnect = false;
			connectPgSql();
			Sleep(300);
		}
	}
}

pqxx::result PgSql::query(std::string strSQL)
{
	pqxx::work trans(*conn_Pg);
	pqxx::result res = trans.exec(strSQL);
	trans.commit();

	return res;
}

void PgSql::disconectPgSql()
{
	if (conn_Pg)
		conn_Pg->close();
}