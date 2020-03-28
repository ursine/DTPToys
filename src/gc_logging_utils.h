//
// Created by bear on 3/28/20.
//

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GC {

    // register or create a named logger
    inline std::shared_ptr<spdlog::logger> log_get(const std::string& name)
    {
        auto log = spdlog::get(name);
        if (log == nullptr) {
            log = spdlog::stdout_color_mt(name);
        }
        return log;
    }


}

