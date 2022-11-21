#ifndef LOGGER_LOGGER_IMPL_HPP
#define LOGGER_LOGGER_IMPL_HPP

#include "logger.hpp"

namespace logger
{

class logger_impl: public logger
{
    void log(std::string const& log_text) const;
};

}

#endif //LOGGER_LOGGER_IMPL_HPP
