// TestAsio.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <iostream>
#include "httpserver.h"

using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	hollow::http::HttpServer s("0.0.0.0", "80","/usr/local/html", 1);
	s.run();
	return 0;
}


