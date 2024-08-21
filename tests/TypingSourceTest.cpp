#include <gtest/gtest.h>
#include "TypingSource.hpp"

TEST(TypingSourceTest, EmptySourceTest)
{
    TypingSource ts;

    EXPECT_TRUE(ts.next().isEmpty());
    EXPECT_TRUE(ts.next().isEmpty());

    ASSERT_EQ(ts.peekChar(), '\0');
}
