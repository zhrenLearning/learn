#include "HttpResponse.h"

using namespace hollow::http;

namespace status_strings {
	const std::string ok =
		"HTTP/1.0 200 OK\r\n";
	const std::string created =
		"HTTP/1.0 201 Created\r\n";
	const std::string accepted =
		"HTTP/1.0 202 Accepted\r\n";
	const std::string no_content =
		"HTTP/1.0 204 No Content\r\n";
	const std::string multiple_choices =
		"HTTP/1.0 300 Multiple Choices\r\n";
	const std::string moved_permanently =
		"HTTP/1.0 301 Moved Permanently\r\n";
	const std::string moved_temporarily =
		"HTTP/1.0 302 Moved Temporarily\r\n";
	const std::string not_modified =
		"HTTP/1.0 304 Not Modified\r\n";
	const std::string bad_request =
		"HTTP/1.0 400 Bad Request\r\n";
	const std::string unauthorized =
		"HTTP/1.0 401 Unauthorized\r\n";
	const std::string forbidden =
		"HTTP/1.0 403 Forbidden\r\n";
	const std::string not_found =
		"HTTP/1.0 404 Not Found\r\n";
	const std::string internal_server_error =
		"HTTP/1.0 500 Internal Server Error\r\n";
	const std::string not_implemented =
		"HTTP/1.0 501 Not Implemented\r\n";
	const std::string bad_gateway =
		"HTTP/1.0 502 Bad Gateway\r\n";
	const std::string service_unavailable =
		"HTTP/1.0 503 Service Unavailable\r\n";

	boost::asio::const_buffer to_buffer(HttpResponse::status_type status)
	{
		switch (status)
		{
		case HttpResponse::ok:
			return boost::asio::buffer(ok);
		case HttpResponse::created:
			return boost::asio::buffer(created);
		case HttpResponse::accepted:
			return boost::asio::buffer(accepted);
		case HttpResponse::no_content:
			return boost::asio::buffer(no_content);
		case HttpResponse::multiple_choices:
			return boost::asio::buffer(multiple_choices);
		case HttpResponse::moved_permanently:
			return boost::asio::buffer(moved_permanently);
		case HttpResponse::moved_temporarily:
			return boost::asio::buffer(moved_temporarily);
		case HttpResponse::not_modified:
			return boost::asio::buffer(not_modified);
		case HttpResponse::bad_request:
			return boost::asio::buffer(bad_request);
		case HttpResponse::unauthorized:
			return boost::asio::buffer(unauthorized);
		case HttpResponse::forbidden:
			return boost::asio::buffer(forbidden);
		case HttpResponse::not_found:
			return boost::asio::buffer(not_found);
		case HttpResponse::internal_server_error:
			return boost::asio::buffer(internal_server_error);
		case HttpResponse::not_implemented:
			return boost::asio::buffer(not_implemented);
		case HttpResponse::bad_gateway:
			return boost::asio::buffer(bad_gateway);
		case HttpResponse::service_unavailable:
			return boost::asio::buffer(service_unavailable);
		default:
			return boost::asio::buffer(internal_server_error);
		}
	}
}

HttpResponse::HttpResponse()
{
}

HttpResponse::~HttpResponse()
{
}

std::vector<boost::asio::const_buffer> HttpResponse::to_buffers()
{
	std::vector<boost::asio::const_buffer> buffers;
	buffers.push_back(status_strings::to_buffer(status_));
	for (std::size_t i = 0; i < headers_.size(); ++i)
	{
		header& h = headers_[i];
		buffers.push_back(boost::asio::buffer(h.field));
		buffers.push_back(boost::asio::buffer(name_value_separator));
		buffers.push_back(boost::asio::buffer(h.value));
		buffers.push_back(boost::asio::buffer(crlf));
	}
	buffers.push_back(boost::asio::buffer(crlf));
	buffers.push_back(boost::asio::buffer(content));
	return buffers;
}