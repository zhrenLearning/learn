#ifndef SERVICEPOOL_H
#define SERVICEPOOL_H

#include <boost/asio.hpp>
#include <vector>
#include <memory>

namespace hollow
{
namespace http
{

class ServicePool
{
public:
    explicit ServicePool(std::size_t pool_size);
	~ServicePool()
	{

	}

    void run();
    void stop();
    boost::asio::io_service& get_service();

private:
    typedef std::shared_ptr<boost::asio::io_service> io_service_ptr;
    typedef std::shared_ptr<boost::asio::io_service::work> work_ptr;

    std::vector<io_service_ptr> io_services_;
    std::vector<work_ptr> work_;

    std::size_t next_io_service_;
};

} //namesapce http
} //namespace hollow

#endif // SERVICEPOOL_H
