#include "servicepool.h"
#include <thread>
#include <functional>
#include <assert.h>

using namespace hollow::http;

ServicePool::ServicePool(std::size_t pool_size)
    : next_io_service_(0)
{
    assert(pool_size != 0);
    for(std::size_t i = 0; i < pool_size; ++i)
    {
        io_service_ptr io_service(new boost::asio::io_service);
        work_ptr work(new boost::asio::io_service::work(*io_service));
        io_services_.push_back(io_service);
        work_.push_back(work);
    }
}

void ServicePool::run()
{
    std::vector<std::thread> threads;
    for(std::size_t i = 0; i < io_services_.size(); ++i)
    {
        threads.emplace_back([this, i]
        {
            io_services_[i]->run();
        });
    }
    for (std::size_t i = 0; i < threads.size(); ++i)
      threads[i].join();
}

void ServicePool::stop()
{
  // Explicitly stop all io_services.
  for (std::size_t i = 0; i < io_services_.size(); ++i)
    io_services_[i]->stop();
}

boost::asio::io_service& ServicePool::get_service()
{
  // Use a round-robin scheme to choose the next io_service to use.
  boost::asio::io_service& io_service = *io_services_[next_io_service_];
  ++next_io_service_;
  if (next_io_service_ == io_services_.size())
    next_io_service_ = 0;
  return io_service;
}
