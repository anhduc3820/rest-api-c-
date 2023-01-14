#ifndef PgSql_HEADER
#define PgSql_HEADER

#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include "Config.h"


class PgSql
{
public:
	PgSql();
	PgSql(std::string hostPg, std::string portPg, std::string userPg, std::string passwordPg, std::string dbnamePg);
	~PgSql();

	pqxx::connection* conn_Pg;
	bool isConnect;

	void connectPgSql();
	void disconectPgSql();
	pqxx::result query(std::string strSQL);


private:
	std::string host;
	std::string port;
	std::string user;
	std::string password;
	std::string dbname;
};

#endif