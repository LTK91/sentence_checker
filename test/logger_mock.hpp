#ifndef LOGGER_MOCK_HPP
#define LOGGER_MOCK_HPP

#include <gmock/gmock.h>
#include <logger/logger.hpp>

namespace logger
{
class logger_mock: public logger
{
public:
    MOCK_CONST_METHOD1(log, void(std::string const&));
};
}



#endif //LOGGER_MOCK_HPP
