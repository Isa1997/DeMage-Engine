#include "precomp.h"

#include "src/Logger/Logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <ctime>

#ifdef WINDOWS
#include <spdlog/sinks/msvc_sink.h>
using consoleSink_t = spdlog::sinks::windebug_sink_st;
#endif

#ifdef LINUX
#include <spdlog/sinks/stdout_sinks.h>
using consoleSink_t = spdlog::sinks::stdout_sink_st;
#endif

using fileSink_t = spdlog::sinks::basic_file_sink_st;

void Engine::Logger::Init()
{
    time_t t = time(0);
    struct tm* now = localtime(&t);
    std::string buffer(80, '\0');
    strftime(&buffer[0], buffer.size(), "%d-%m-%y_%H-%M-%S.log", now);

    auto consoleSink = std::make_shared<consoleSink_t>();
    auto fileSink = std::make_shared<fileSink_t>("logs/log_" + buffer, true);
    
    ms_Logger = std::make_unique<spdlog::logger>("multi_sink", spdlog::sinks_init_list{ consoleSink, fileSink });
}
