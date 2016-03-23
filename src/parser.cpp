#include "parser.hpp"
#include "connection.hpp"

using namespace hollow::http;
using namespace http::server2;

int OnMessageBeginCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
	con->http_request_parser = new HttpRequest();
	return 0;
}

int OnUrlCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
	con->http_request_parser->http_url.assign(at, length);
	return 0;
}

int OnHeaderFieldCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
	con->http_request_parser->http_header_field.assign(at, length);
	return 0;
}

int OnHeaderValueCallback(http_parser *parser, const char *at, size_t length)
{
	connection      *con = (connection*)parser->data;
	HttpRequest *request = con->http_request_parser;
	request->http_headers[request->http_header_field] = std::string(at, length);
	return 0;
}

int OnHeadersCompleteCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
	HttpRequest *request = con->http_request_parser;
	request->http_method = http_method_str((http_method)parser->method);
	return 0;
}

int OnBodyCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
	con->http_request_parser->http_body.append(at, length);
	return 0;
}

int OnMessageCompleteCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
	HttpRequest *request = con->http_request_parser;
	con->http_request_parser = NULL;
	return 0;
}


void HttpParser::initParser()
{
	settings.on_message_begin = OnMessageBeginCallback;
	settings.on_message_complete = OnMessageCompleteCallback;
	settings.on_headers_complete = OnHeadersCompleteCallback;
	settings.on_header_field = OnHeaderFieldCallback;
	settings.on_header_value = OnHeaderValueCallback;
	settings.on_url = OnUrlCallback;
	settings.on_body = OnBodyCallback;

	http_parser_init(&parser, HTTP_REQUEST);
}

int HttpParser::parserRequest(const std::string &inbuf)
{
	std::cout << inbuf << std::endl;
    int nparsed = http_parser_execute(&parser, &settings, inbuf.c_str(), inbuf.size());
    if (parser.http_errno != HPE_OK)
    {
        return -1;
    }
    return nparsed;
}



/*
int HttpParser::OnMessageBeginCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
    con->http_request_parser = new HttpRequest();
    return 0;
}

int HttpParser::OnUrlCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
    con->http_request_parser->http_url.assign(at, length);
    return 0;
}

int HttpParser::OnHeaderFieldCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
    con->http_request_parser->http_header_field.assign(at, length);
    return 0;
}

int HttpParser::OnHeaderValueCallback(http_parser *parser, const char *at, size_t length)
{
	connection      *con = (connection*)parser->data;
    HttpRequest *request = con->http_request_parser;
    request->http_headers[request->http_header_field] = std::string(at, length);
    return 0;
}

int HttpParser::OnHeadersCompleteCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
    HttpRequest *request = con->http_request_parser;
    request->http_method    = http_method_str((http_method)parser->method);
    return 0;
}

int HttpParser::OnBodyCallback(http_parser *parser, const char *at, size_t length)
{
	connection *con = (connection*)parser->data;
    con->http_request_parser->http_body.append(at, length); 
    return 0;
}

int HttpParser::OnMessageCompleteCallback(http_parser *parser)
{
	connection *con = (connection*)parser->data;
    HttpRequest *request = con->http_request_parser;
    con->http_request_parser = NULL;
    return 0;
}
*/