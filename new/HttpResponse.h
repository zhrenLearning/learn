#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include <string>
#include <vector>
#include <boost/asio.hpp>

namespace hollow {
namespace http {

struct header
{
	std::string field;
	std::string value;
};

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

class HttpResponse
{
public:
	enum status_type
	{
		ok = 200,
		created = 201,
		accepted = 202,
		no_content = 204,
		multiple_choices = 300,
		moved_permanently = 301,
		moved_temporarily = 302,
		not_modified = 304,
		bad_request = 400,
		unauthorized = 401,
		forbidden = 403,
		not_found = 404,
		internal_server_error = 500,
		not_implemented = 501,
		bad_gateway = 502,
		service_unavailable = 503
	} status_;
public:
	HttpResponse();
	~HttpResponse();

	std::vector<header> headers_;
	std::string content;
	std::vector<boost::asio::const_buffer> to_buffers();
};

} //namespace http
} //namespace hollow

#endif

