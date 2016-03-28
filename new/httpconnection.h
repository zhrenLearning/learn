#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <boost/asio.hpp>
#include <array>
#include <memory>
#include "http_parser.h"
#include "parser.hpp"
#include "HttpHandle.h"
#include "HttpResponse.h"


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

			explicit HttpConnection(boost::asio::io_service& io_service, std::shared_ptr<hollow::http::HttpHandle>& httpHandle);
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
		};
		typedef std::shared_ptr<HttpConnection> connection_ptr;

		namespace file_types
		{
			static struct mapping
			{
				const char* extension;
				const char* mime_type;
			} mappings[] =
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
}
}


#endif // HTTPCONNECTION_H
