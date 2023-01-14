// engine-trade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Application.h"
#include <cpprest/http_listener.h>
#include <spdlog/spdlog.h>


Application* app = new Application();

void handleRequest(web::http::http_request request)
{
    utility::string_t request_str = request.to_string();
    SPDLOG_INFO("Recived request {}", utility::conversions::to_utf8string(request_str));

    auto path = web::uri::split_path(web::uri::decode(request.relative_uri().path()));

    // define path
    std::wstring path_user = L"user";

    // get method
    web::http::method method = request.method();

    if (path.size() == 1 && path[0] == path_user)
    {

        if (method == web::http::methods::GET)
        {
            app->getUsers();
            SPDLOG_INFO("DONE handle GET ! ");
            request.reply(web::http::status_codes::OK, "DONE !");
        }
        else
        {
            request.reply(web::http::status_codes::MethodNotAllowed, "DONE !");
        }
    }
    else if (path.size() == 2)
    {
        request.reply(web::http::status_codes::NotFound);
    }
    else
    {
        request.reply(web::http::status_codes::NotFound);
    }
}

int main()
{
    web::http::experimental::listener::http_listener httpListener(L"http://localhost:8088");
    httpListener.support(handleRequest);
    httpListener.open().then([&httpListener]() {}).wait();
    SPDLOG_INFO("INIT REST SUCCESS -> START LISTEN REQUEST !");

	if (app->initApp())
		app->run();

	app->shutdown();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
