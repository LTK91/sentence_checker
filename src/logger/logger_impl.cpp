#include "logger_impl.hpp"

#include <iostream>

namespace logger
{

void logger_impl::log(std::string const& log_text) const
{
    std::cout << log_text << std::endl;
}

}