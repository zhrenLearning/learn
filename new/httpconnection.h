#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <boost/asio.hpp>
#include <array>
#include <memory>
#include "http_parser.h"
#include "parser.hpp"
#include "HttpHandle.h"
#include "HttpResponse.h"

#include "mysql_connection.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


namespace hollow
{
namespace http
{
//	class HttpHandle;

		class HttpConnection : public std::enable_shared_from_this<HttpConnection>
		{
		public:
			HttpConnection(const HttpConnection&) = delete;
			HttpConnection& operator= (const HttpConnection&) = delete;

			explicit HttpConnection(boost::asio::io_service& io_service, std::shared_ptr<hollow::http::HttpHandle>& httpHandle, std::shared_ptr<sql::Connection> conn_ptr);
			~HttpConnection();
			boost::asio::ip::tcp::socket& socket();
			void start();

		private:
			void handle_read();
			void handle_write();

			boost::asio::ip::tcp::socket socket_;
			std::array<char, 16384> buffer_;

		public:
			hollow::http::HttpParser http_parser_;
			std::shared_ptr<hollow::http::HttpRequest> http_request_parser;
			std::shared_ptr<hollow::http::HttpResponse> http_response_parser;
			std::shared_ptr<hollow::http::HttpHandle>& httpHandle_;
			std::shared_ptr<sql::Connection> conn_ptr_;
		};
		typedef std::shared_ptr<HttpConnection> connection_ptr;

		namespace file_types
		{
			static struct mapping
			{
				const char* extension;
				const char* mime_type;
			} mappings[]=
			{
				{ "gif", "image/gif" },
				{ "htm", "text/html" },
				{ "html", "text/html" },
				{ "jpg", "image/jpeg" },
				{ "png", "image/png" },
				{ "css", "text/css" },
				{ "ico", "application/x-ico" }
			};
			static std::string extension_to_type(const std::string& extension)
			{
				for (mapping m : mappings)
				{
					if (m.extension == extension)
					{
						return m.mime_type;
					}
				}
				return "text/plain";
			}
		}

		namespace static_html
		{
			static struct html_mapping
			{
				const char* url_get;
				const char* url_html;
			} html_map[] = 
			{
				{"show.html?device_type=1&damage_type=1", "01-01.html"},
				{"show.html?device_type=1&damage_type=2", "01-02.html"}
			};

			inline static std::string url_to_html(const std::string& url)
			{
				for(static_html s : html_map)
				{
					if(s.url_get == url)
					{
						return s.usr_html;
					}
				}
				return "";
			}
		}
}
}


#endif // HTTPCONNECTION_H
