#ifndef CONNECTION_POOL_H_
#define CONNECTION_POOL_H_

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <vector>

namespace hollow
{
namespace http
{
class ConntionPool
{
public:
	explicit ConntionPool(std::size_t pool_size);
	~ConntionPool();

	std::shared_ptr<sql::Connection>& get_conn();
private:
	typedef std::shared_ptr<sql::Connection> conn_ptr;
	std::vector<conn_ptr> conn_ptrs_;
	std::size_t next_conn_ptr_;
};
} //namespace http
} //namespace hollow
#endif
