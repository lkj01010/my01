#pragma once

#include <boost/thread.hpp>

typedef boost::shared_mutex rw_mutex;
typedef boost::shared_lock<rw_mutex>    read_lock;
typedef boost::unique_lock<rw_mutex>    write_lock;