#include "HttpHandle.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace hollow::http;
using namespace std;

HttpHandle::HttpHandle(const string& doc_root) : doc_root_(doc_root)
{
}


HttpHandle::~HttpHandle()
{
}

void HttpHandle::handle(std::shared_ptr<HttpConnection> httpConnection)
{
	std::string request_path;
	if (!url_decode(httpConnection->http_request_parser->http_url, request_path))
	{
		request_path = "/index.html";
	}

	if (request_path.empty() || request_path[0] != '/' || request_path.find("..") != std::string::npos)
	{
		request_path = "/index.html";
	}

	if (request_path[request_path.size() - 1] == '/')
	{
		request_path += "index.html";
	}

	std::size_t last_slash_pos = request_path.find_last_of("/");
	std::size_t last_dot_pos = request_path.find_last_of(".");
	std::string extension;
	if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
	{
		extension = request_path.substr(last_dot_pos + 1);
	}

	if (extension.empty())
	{
		request_path += "/index.html";
		extension = "html";
	}

	httpConnection->http_response_parser->status_ = HttpResponse::ok;
	std::string full_path = doc_root_ + request_path;
	std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
	if (!is)
	{
		std::string full_path = doc_root_ + "/noexist.html";
		std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
		if (!is)
		{
			return;
		}
		else
		{
			char buf[1024];
			while (is.read(buf, sizeof(buf)).gcount() > 0)
				httpConnection->http_response_parser->content.append(buf, is.gcount());
			httpConnection->http_response_parser->headers_.resize(2);
			httpConnection->http_response_parser->headers_[0].field = "Content-Length";
			httpConnection->http_response_parser->headers_[0].value = std::to_string(httpConnection->http_response_parser->content.size());
			httpConnection->http_response_parser->headers_[1].field = "Content-Type";
			httpConnection->http_response_parser->headers_[1].value = file_types::extension_to_type(extension);
		}
	}
	else
	{
		char buf[1024];
		while (is.read(buf, sizeof(buf)).gcount() > 0)
			httpConnection->http_response_parser->content.append(buf, is.gcount());
		httpConnection->http_response_parser->headers_.resize(2);
		httpConnection->http_response_parser->headers_[0].field = "Content-Length";
		httpConnection->http_response_parser->headers_[0].value = std::to_string(httpConnection->http_response_parser->content.size());
		httpConnection->http_response_parser->headers_[1].field = "Content-Type";
		httpConnection->http_response_parser->headers_[1].value = file_types::extension_to_type(extension);
	}
}

bool HttpHandle::url_decode(const std::string& in, std::string& out)
{
	out.clear();
	out.reserve(in.size());
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%')
		{
			if (i + 3 <= in.size())
			{
				int value = 0;
				std::istringstream is(in.substr(i + 1, 2));
				if (is >> std::hex >> value)
				{
					out += static_cast<char>(value);
					i += 2;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else
		{
			out += in[i];
		}
	}
	return true;
}
