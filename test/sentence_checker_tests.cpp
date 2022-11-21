#include <gtest/gtest.h>

#include "logger_mock.hpp"
#include <sentence_checker/sentence_checker.hpp>

namespace sentence_checker
{
namespace
{
std::string const invalid_sentence_lowercase_first_letter =
    "invalid sentence with lowercase first letter.";
std::string const invalid_sentence_uncapitalisable_first_character =
    " Invalid sentence with space for first character.";
std::string const invalid_sentence_misplaced_period_middle =
    "Invalid sentence with \".\" in the middle.";
std::string const invalid_sentence_misplaced_period_start =
    ".Invalid sentence with \".\" at the start.";
std::string const invalid_sentence_misplaced_period_end =
    "Invalid sentence with two \".\" at the end..";
std::string const invalid_sentence_odd_quotations =
    "Invalid sentence with uneven number of \"\"\".";
std::string const invalid_sentence_more_odd_quotations =
    "Invalid \"sen\"tence with uneven number of \"\"\".";
std::string const invalid_sentence_final_char_letter =
    "Invalid sentence with invalid final character";
std::string const invalid_sentence_final_char_number =
    "Invalid sentence with invalid final character 1";
std::string const invalid_sentence_final_char_space =
    "Invalid sentence with invalid final character ";
std::string const invalid_sentence_unwritten_number_zero =
    "Invalid sentence with number 0.";
std::string const invalid_sentence_unwritten_number_one =
    "Invalid sentence with number 1.";
std::string const invalid_sentence_unwritten_number_two_leading_zero =
    "Invalid sentence with number 02.";
std::string const invalid_sentence_unwritten_number_twelve =
    "Invalid sentence with number 12.";
std::string const log_unwritten_number =
    "Sentence invalid, numbers below 13 must be written "
    "as words. Sentence: ";
std::string const log_uncapitalised_first_letter =
    "Sentence invalid due to uncapitalised first letter. "
    "Sentence: ";
std::string const log_misplaced_period =
    "Sentence invalid, contains '.' in position "
    "other than final character. Sentence: ";
std::string const log_odd_quotations =
    "Sentence invalid, contains odd number of '\"'. "
    "Sentence: ";
std::string const log_invalid_final_char =
    "Sentence contains invalid final character, must be"
    " '!', '?' or '.'. Sentence: ";
}
class SentenceCheckerTests : public testing::Test
{
protected:
    SentenceCheckerTests()
        : logger_mock_(std::make_shared<logger::logger_mock>()),
          checker_(logger_mock_)
    {
    }

    std::shared_ptr<logger::logger_mock> const logger_mock_;
    sentence_checker const checker_;
};

class SentenceCheckerTestsValidParameterised :
    public SentenceCheckerTests,
    public testing::WithParamInterface<std::string>
{
};

TEST_P(SentenceCheckerTestsValidParameterised,
       ValidateSentenceWillReturnTrueForValidSentence)
{
    EXPECT_TRUE(checker_.validate_sentence(GetParam()));
}

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsParameterisedInstance,
    SentenceCheckerTestsValidParameterised,
    testing::Values(
        "Valid sentence with full stop.",
        "Valid sentence with question?",
        "Valid sentence with exclamation!",
        "Valid sentence with the number one.",
        "Valid sentence with the number twelve.",
        "Valid sentence with the number 13.",
        "Valid sentence with the number 100.",
        "Valid sentence with \"even quotes\".",
        "Valid sentence with more \"ev\"\"\"en quotes.",
        "Valid question with \"even quotes\" and one small number?",
        "Valid exclamation with \"even quotes\" and the number 13!"));

class SentenceCheckerTestsInvalidParameterised :
    public SentenceCheckerTests,
    public testing::WithParamInterface<std::pair<std::string, std::string> >
{
};

TEST_P(SentenceCheckerTestsInvalidParameterised,
       ValidateSentenceWillReturnFalseForInvalidSentence)
{
    EXPECT_CALL(*logger_mock_, log(GetParam().first));

    EXPECT_FALSE(checker_.validate_sentence(GetParam().second));
}

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidContainsNoCharacters,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            "Sentence invalid as it contains no characters.",
            "")));

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidMisplacedPeriod,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            log_misplaced_period +
            invalid_sentence_misplaced_period_middle,
            invalid_sentence_misplaced_period_middle),
        std::make_pair(
            log_misplaced_period +
            invalid_sentence_misplaced_period_end,
            invalid_sentence_misplaced_period_end),
        std::make_pair(
            log_uncapitalised_first_letter +
            invalid_sentence_misplaced_period_start,
            invalid_sentence_misplaced_period_start)));

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidFirstLetter,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            log_uncapitalised_first_letter + invalid_sentence_uncapitalisable_first_character,
            invalid_sentence_uncapitalisable_first_character),
        std::make_pair(
            log_uncapitalised_first_letter + invalid_sentence_lowercase_first_letter,
            invalid_sentence_lowercase_first_letter)));

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidFinalLetter,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            log_invalid_final_char + invalid_sentence_final_char_letter,
            invalid_sentence_final_char_letter),
        std::make_pair(
            log_invalid_final_char + invalid_sentence_final_char_number,
            invalid_sentence_final_char_number),
        std::make_pair(
            log_invalid_final_char + invalid_sentence_final_char_space,
            invalid_sentence_final_char_space)));

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidContainsOddQuotations,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            log_odd_quotations + invalid_sentence_odd_quotations,
            invalid_sentence_odd_quotations),
        std::make_pair(
            log_odd_quotations + invalid_sentence_more_odd_quotations,
            invalid_sentence_more_odd_quotations)));

INSTANTIATE_TEST_CASE_P(
    SentenceCheckerTestsInvalidUnwrittenNumbers,
    SentenceCheckerTestsInvalidParameterised,
    testing::Values(
        std::make_pair(
            log_unwritten_number + invalid_sentence_unwritten_number_zero,
            invalid_sentence_unwritten_number_zero),
        std::make_pair(
            log_unwritten_number + invalid_sentence_unwritten_number_two_leading_zero,
            invalid_sentence_unwritten_number_two_leading_zero),
        std::make_pair(
            log_unwritten_number + invalid_sentence_unwritten_number_one,
            invalid_sentence_unwritten_number_one),
        std::make_pair(
            log_unwritten_number + invalid_sentence_unwritten_number_twelve,
            invalid_sentence_unwritten_number_twelve)));

}

