#include <gmock/gmock.h>

#include <stringzeug/manipulation.h>


using namespace stringzeug;


class manipulation_test : public testing::Test
{
public:
    manipulation_test()
    {
    }

protected:
};

TEST_F(manipulation_test, join)
{
    std::vector<std::string> vec {"string", "to", "concatenate"};
    std::string res = join(vec, "-");

    ASSERT_EQ("string-to-concatenate", res);
}

TEST_F(manipulation_test, trim)
{
    std::string stringWithWhitespaces = "   This is a string.     ";
    std::string trim1 = trim(stringWithWhitespaces);
    std::string trim2 = trim(stringWithWhitespaces, true);

    ASSERT_EQ("This is a string.", trim1);
    ASSERT_EQ("Thisisastring.", trim2);
}

TEST_F(manipulation_test, parseArray)
{
    std::string stringArray = "(element1, element2   ,element3,element4)";
    std::vector<std::string> vec = parseArray(stringArray, 4);
    std::vector<std::string> vecComp {"element1", "element2", "element3", "element4"};

    ASSERT_EQ(vecComp, vec);
}

TEST_F(manipulation_test, split)
{
    std::string inputString = "seperate this - by-minus-  sign.-?";
    std::vector<std::string> vec = split(inputString, '-');
    std::vector<std::string> vecComp {"seperate this ", " by", "minus", "  sign.", "?"};

    ASSERT_EQ(vecComp, vec);
}
