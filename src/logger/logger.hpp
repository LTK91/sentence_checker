#ifndef LOGGER_LOGGER_HPP
#define LOGGER_LOGGER_HPP

#include <string>

namespace logger
{

class logger
{
public:
    /**
     * @brief logs text
     *
     * @param [in] log_text text to log
     */
    virtual void log(std::string const& log_text) const = 0;
};

}

#endif //LOGGER_LOGGER_HPP
