#include "httpserver.h"
#include <boost/bind.hpp>

using namespace hollow::http;

HttpServer::HttpServer(const std::string& address, const std::string& port,
    const std::string& doc_root, std::size_t io_service_pool_size)
  : service_pool_(io_service_pool_size),
    signals_(service_pool_.get_service()),
    acceptor_(service_pool_.get_service()),
	httpHandle(std::make_shared<HttpHandle>(doc_root)),
	connection_pool_(io_service_pool_size)
{
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
  #if defined(SIGQUIT)
    signals_.add(SIGQUIT);
  #endif // defined(SIGQUIT)
    signals_.async_wait(std::bind(&HttpServer::handle_stop, this));

    boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
    boost::asio::ip::tcp::resolver::query query(address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    start_accept();
}

void HttpServer::run()
{
    service_pool_.run();
}

void HttpServer::start_accept()
{
    new_connection_.reset(new HttpConnection(service_pool_.get_service(), httpHandle));
    acceptor_.async_accept(new_connection_->socket(), boost::bind(&HttpServer::handle_accept, this, boost::asio::placeholders::error));
}

void HttpServer::handle_accept(const boost::system::error_code& e)
{
    if (!e)
    {
      new_connection_->start();
    }
    start_accept();
}

void HttpServer::handle_stop()
{
    service_pool_.stop();
}
