#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include "servicepool.h"
#include "httpconnection.h"
#include "conntionpool.h"

namespace hollow
{
namespace http
{

class HttpHandle;

class HttpServer
{
public:
    explicit HttpServer(const std::string& address, const std::string& port,
                        const std::string& doc_root, std::size_t io_service_pool_size);

    void run();

	std::shared_ptr<hollow::http::HttpHandle> httpHandle;

private:
    void start_accept();
    void handle_accept(const boost::system::error_code& e);
    void handle_stop();

    hollow::http::ServicePool service_pool_;
	hollow::http::ConntionPool connection_pool_;
    boost::asio::signal_set signals_;
    boost::asio::ip::tcp::acceptor acceptor_;

    connection_ptr new_connection_;
};



} // namesapce http
} // namespace hollow

#endif // HTTPSERVER_H
