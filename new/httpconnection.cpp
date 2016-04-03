#include "httpconnection.h"
#include <vector>
#include <iostream>
#include <thread>
#include "http_parser.h"

using namespace hollow::http;
using namespace std;
using namespace hollow::http::file_types;


HttpConnection::HttpConnection(boost::asio::io_service& io_service, std::shared_ptr<hollow::http::HttpHandle>& httpHandle, std::shared_ptr<sql::Connection> conn_ptr)
: socket_(io_service), httpHandle_(httpHandle), conn_ptr_(conn_ptr)
{

}

HttpConnection::~HttpConnection()
{
}

boost::asio::ip::tcp::socket& HttpConnection::socket()
{
	return socket_;
}

void HttpConnection::start()
{
	http_parser_.initParser();
	http_parser_.parser.data = this;
	this->handle_read();
}

void HttpConnection::handle_read()
{
	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(buffer_),
		[this, self](boost::system::error_code ec, std::size_t bytes_transferred)
	{
		if (!ec)
		{
			string temp(buffer_.data(), bytes_transferred);
			cout << temp << endl;
			//int ret = http_parser_.parserRequest(temp);
			int ret = http_parser_.parserRequest(buffer_.data(), bytes_transferred);
			if (ret == -1)
			{
				//bad
				handle_write();
			}
			else if (ret <= bytes_transferred)
			{
				//good
	//			cout << this->http_request_parser->http_url << endl;
				http_response_parser = make_shared<HttpResponse>();
				httpHandle_->handle(shared_from_this());
				handle_write();
			}
			else
			{
				handle_read();
			}
		}
		else if (ec != boost::asio::error::operation_aborted)
		{
			socket_.close();
		}
	});
}

void HttpConnection::handle_write()
{
	auto self(shared_from_this());
	boost::asio::async_write(socket_, http_response_parser->to_buffers(),
		[this, self](boost::system::error_code ec, std::size_t)
	{
		if (!ec)
		{
			boost::system::error_code ignored_ec;
			socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		}
		else
		{
			socket_.close();
		}
	});
}
