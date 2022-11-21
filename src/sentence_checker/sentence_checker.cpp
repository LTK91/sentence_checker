#include "sentence_checker.hpp"

#include <cctype>
#include <regex>
#include <stack>

namespace sentence_checker
{

sentence_checker::sentence_checker(std::shared_ptr<logger::logger> const& logger)
    : logger_(logger)
{
}

bool sentence_checker::validate_sentence(std::string const &sentence) const
{
    if (sentence.size() == 0)
    {
        logger_->log("Sentence invalid as it contains no characters.");
        return false;
    }

    if (!check_first_character(sentence))
    {
        logger_->log("Sentence invalid due to uncapitalised first letter. "
                     "Sentence: " + sentence);
        return false;
    }

    if (!check_final_character(sentence))
    {
        logger_->log("Sentence contains invalid final character, must be"
                     " '!', '?' or '.'. Sentence: " + sentence);
        return false;
    }

    if (!check_written_numbers(sentence))
    {
        logger_->log("Sentence invalid, numbers below 13 must be written "
                     "as words. Sentence: " + sentence);
        return false;
    }

    if (!check_sentence_body(sentence))
    {
        return false;
    }

    return true;

}

bool sentence_checker::check_first_character(std::string const &sentence) const
{
    if (!std::isupper(static_cast<unsigned char>(sentence.front())))
    {
        return false;
    }

    return true;
}

bool sentence_checker::check_sentence_body(std::string const &sentence) const
{
    std::string::const_iterator it = sentence.begin();

    unsigned int count = 0;

    while (it != (sentence.end() - 1))
    {
        if (*it == '.')
        {
            logger_->log("Sentence invalid, contains '.' in position "
                         "other than final character. Sentence: " + sentence);
            return false;
        }
        else if (*it == '"')
        {
            ++count;
        }

        ++ it;
    }

    if (count % 2 != 0)
    {
        logger_->log("Sentence invalid, contains odd number of '\"'. "
                     "Sentence: " + sentence);
        return false;
    }

    return true;
}

bool sentence_checker::check_final_character(std::string const &sentence) const
{
    unsigned char const final_char = sentence.back();

    if (final_char != '.' &&
        final_char != '?' &&
        final_char != '!')
    {
        return false;
    }

    return true;
}

bool sentence_checker::check_written_numbers(std::string const &sentence) const
{
    //matches against numbers 12 and below written as numerals
    //includes numbers 9 and below with a leading zero
    if (std::regex_search(sentence, std::regex("\\b([0-9]|0[0-9]|1[0-2])\\b")))
    {
        return false;
    }

    return true;
}
}