#ifndef HTTP_HANDLE_H_
#define HTTP_HANDLE_H_

#include <string>
#include <memory>
//#include "httpconnection.h"

namespace hollow
{
namespace http
{
class HttpConnection;
}
}

namespace hollow
{
namespace http
{

//class HttpConnection;
class HttpHandle
{
public:
	HttpHandle(const HttpHandle&) = delete;
	HttpHandle& operator=(const HttpHandle&) = delete;
	explicit HttpHandle(const std::string& doc_root);
	~HttpHandle();

	void handle(std::shared_ptr<hollow::http::HttpConnection> httpConnection);
private:
	std::string doc_root_;
	static bool url_decode(const std::string& in, std::string& out);
};
} //namesapce http
} //namespace hollow
#include "httpconnection.h"

#endif

