#include <logging_research.h>


namespace ResearchLog {

    ResearchLogger::ResearchLogger() {
        this->sink_get = init_logging("get_block");
        this->sink_proc = init_logging("proc_block");
        this->sink_send_inv = init_logging("send_inv_block");
    }

    boost::shared_ptr <sink_t> ResearchLogger::init_logging(std::string filter_name) {
        boost::shared_ptr <logging::core> core = logging::core::get();

        boost::shared_ptr <sinks::text_file_backend> backend =
                boost::make_shared<sinks::text_file_backend>(
                        keywords::auto_flush = true,
                        keywords::file_name = filter_name + "_%Y-%m-%d_%H-%M-%S.%N.log",
                        keywords::time_based_rotation = sinks::file::rotation_at_time_interval(
                                boost::posix_time::hours(1)));

        boost::shared_ptr <sink_t> sink(new sink_t(backend));
        sink->set_filter(research_channel == filter_name);
        core->add_sink(sink);

        return sink;
    }

    void ResearchLogger::stop_logging(boost::shared_ptr <sink_t> &sink) {
        boost::shared_ptr <logging::core> core = logging::core::get();
        core->remove_sink(sink);
        sink->stop();
        sink->flush();
        sink.reset();
    }

    ResearchLogger::~ResearchLogger() {
        stop_logging(this->sink_get);
        stop_logging(this->sink_proc);
        stop_logging(this->sink_send_inv);
    }
}

//void ResearchLog::ResearchLogger::log(const std::string& hash, uint32_t time_invented, uint32_t time_get, uint32_t local_time) {
//    src::severity_channel_logger<severity_level> lg(keywords::channel = "research");
//    BOOST_LOG_SEV(lg, recv_block) << hash << " " << time_invented << " " << time_get << " " << local_time;
//}
