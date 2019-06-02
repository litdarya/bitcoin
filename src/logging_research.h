#pragma once

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/support/date_time.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

namespace ResearchLog {

BOOST_LOG_ATTRIBUTE_KEYWORD(research_channel, "Channel", std::string);
enum class severity_level
{
    stats
};

typedef sinks::asynchronous_sink<boost::log::sinks::text_file_backend> sink_t;
typedef src::severity_channel_logger<severity_level, std::string> logger_type;

static logger_type lg_get_block(keywords::channel = "get_block");
static logger_type lg_proc_block(keywords::channel = "proc_block");
static logger_type lg_send_inv_block(keywords::channel = "send_inv_block");

class ResearchLogger {
    public:
        ResearchLogger();

        ~ResearchLogger();
    private:
        boost::shared_ptr<sink_t> init_logging(std::string filter_name);
        void stop_logging(boost::shared_ptr<sink_t>& sink);

        boost::shared_ptr<sink_t> sink_get;
        boost::shared_ptr<sink_t> sink_proc;
        boost::shared_ptr<sink_t> sink_send_inv;
};

};

static ResearchLog::ResearchLogger ResearchLogInstance;
