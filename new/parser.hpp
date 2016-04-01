#ifndef HTTP_PARSER_HPP_
#define HTTP_PARSER_HPP_

#include <map>
#include <string>
#include <iostream>
#include "http_parser.h"

namespace hollow {
namespace http{


typedef std::map<std::string, std::string> vec_header_t;

class HttpRequest
{
public:
	HttpRequest()
	{

	}

	~HttpRequest()
	{

	}

	std::string http_header_field;
	std::string http_method;
	std::string http_url;
	std::string http_version;
	vec_header_t http_headers;
	std::string http_body;
};

class HttpParser
{
public:
	HttpParser()
	{

	}
	~HttpParser()
	{

	}

	void initParser();
	int parserRequest(const std::string &inbuf);
	int parserRequest(const char *, const std::size_t &);

public:
	http_parser          parser;
    http_parser_settings settings;
};

/*
static int OnMessageBeginCallback(http_parser *parser);
static int OnUrlCallback(http_parser *parser, const char *at, size_t length);

//int OnHeaderFieldCallback(http_parser *parser, const char *at, size_t length);

int OnHeaderFieldCallback(http_parser *parser, const char *at, size_t length);

int OnHeaderValueCallback(http_parser *parser, const char *at, size_t length);

int OnHeadersCompleteCallback(http_parser *parser);

int OnBodyCallback(http_parser *parser, const char *at, size_t length);

int OnMessageCompleteCallback(http_parser *parser);
*/
} //namespace http
} //namespace hollow
#endif