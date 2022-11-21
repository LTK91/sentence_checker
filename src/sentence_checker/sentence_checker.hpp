#ifndef SENTENCE_CHECKER_SENTENCE_CHECKER_HPP
#define SENTENCE_CHECKER_SENTENCE_CHECKER_HPP

#include "../logger/logger.hpp"
#include <memory>
#include <string>

namespace sentence_checker
{
class sentence_checker
{
public:
    /**
     * @brief  constructs a sentence_checker
     *
     * @param [in] logger to log errors
     */
    sentence_checker(std::shared_ptr<logger::logger> const& logger);
    /**
     * @brief Validates that a string is a valid sentence. Valid sentence:
     *        - begins with a capital letter
     *        - ends with '?', '!' or '.'
     *        - does not contain '.' other than at the end
     *        - spells out numbers below 13 (e.g. 'twelve' rather than '12'); and
     *        - has an even number of quotation marks
     *
     * @param [in] sentence  sentence to validate
     *
     * @return true if valid sentence, otherwise false
     */
    bool validate_sentence(std::string const &sentence) const;

private:
    bool check_first_character(std::string const &sentence) const;

    bool check_sentence_body(std::string const &sentence) const;

    bool check_final_character(std::string const &sentence) const;

    bool check_written_numbers(std::string const &sentence) const;

    std::shared_ptr<logger::logger> const logger_;
};
}

#endif //SENTENCE_CHECKER_SENTENCE_CHECKER_HPP
