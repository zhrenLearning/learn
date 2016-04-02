//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "server.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class Solution
{
public:
	string addBinary(string a, string b)
	{
		string result;
		const size_t n = a.size() > b.size() ? a.size() : b.size();
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		int carry = 0;
		for (size_t i = 0; i < n; i++)
		{
			const int ai = i < a.size() ? a[i] - '0' : 0;
			const int bi = i < b.size() ? b[i] - '0' : 0;
			const int val = (ai + bi + carry) % 2;
			carry = (ai + bi + carry) / 2;
			result.insert(result.begin(), val + '0');
		}
		if (carry == 1)
		{
			result.insert(result.begin(), '1');
		}
		return result;
	}
};

int main(int argc, char* argv[])
{

  try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "Sentimental");
  con->setSchema("db_detail");

  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
  while (res->next()) {
    cout << "\t... MySQL replies: ";
    cout << res->getString("_message") << endl;
    cout << "\t... MySQL says it again: ";
    cout << res->getString(1) << endl;
  }
  delete res;
  delete stmt;
  delete con;

} catch (sql::SQLException &e) {
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

  try
  {
    // Check command line arguments.
	  /*
    if (argc != 5)
    {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 1 .\n";
      return 1;
    }

    // Initialise the server.
    std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
    http::server2::server s(argv[1], argv[2], argv[4], num_threads);

	  string a = "11";
	  string b = "1";
	  Solution sl;
	  string str = sl.addBinary(a, b);
	  cout << str << endl;

	  */
	http::server2::server s("0.0.0.0", "80", "/usr/local/src/learn/html", 4);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}


/*
#include <iostream>
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
*/

/*
#include <string>
#include <iostream>

std::string start()
{
	return "hello world";
};

class temptest
{
public:
	static std::string run()
	{
		return "hello world";
	}
};

int main()
{
	std::string str = temptest::run();
	std::cout << str << std::endl;
	system("pause");
}

*/
/*

using namespace std;

template<typename Iterator, typename T>
struct accumulate_block
{
	void operator () (Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result);
	}
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);
	if (!length)
		return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_thread = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(hardware_thread != 0 ? hardware_thread : 2, max_threads);
	unsigned long const block_size = length / num_threads;
	
	vector<T> results(num_threads);
	vector<thread> threads(num_threads - 1);
	Iterator block_start = first;
	for (int i = 0; i < num_threads - 1; i++)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		threads[i] = thread(accumulate_block<Iterator, T>( ), block_start, block_end, std::ref(results[i]));

		block_start = block_end;
	}

	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 1000; i++)
	{
		vec.push_back(1);
	}
	int sum = parallel_accumulate(vec.begin(), vec.end(), 5);

	std::cout << sum << std::endl;

	system("pause");
	return 0;
}

*/
