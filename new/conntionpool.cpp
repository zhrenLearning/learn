#include "conntionpool.h"
#include <iostream>


using namespace hollow::http;
using namespace sql;
using namespace std;

ConntionPool::ConntionPool(std::size_t pool_size) : next_conn_ptr_(0)
{
	assert(pool_size != 0);
	try
	{
		Driver *driver;
		const char* user = "root";
		const char* passwd = "Sentimental";
		const char* host = "tcp://127.0.0.1:3306";
		driver = get_driver_instance();
		
		for (std::size_t i = 0; i < pool_size; ++i)
		{
			conn_ptrs_.emplace_back(driver->connect(host, user, passwd));
			conn_ptrs_[i]->setSchema("db_detail");
			cout << "connection succ ----- " << i << endl;
		}
	}
	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}

ConntionPool::~ConntionPool()
{
	for (std::size_t i = 0; i < conn_ptrs_.size(); ++i)
	{
		conn_ptrs_[i]->setSchema("db_detail");
		cout << "connection succ ----- " << i << endl;
	}
}

std::shared_ptr<sql::Connection> ConntionPool::get_conn()
{
	std::shared_ptr<sql::Connection> conn_ptr = conn_ptrs_[next_conn_ptr_];
	++next_conn_ptr_;
	if (next_conn_ptr_ == conn_ptrs_.size())
		next_conn_ptr_ = 0;
	return conn_ptr;
}
