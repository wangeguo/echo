#include <gtest/gtest.h>
#include <echo/echo.h>

TEST(EchoTest, InitClass)
{
	echo::Echo e;
}

int main(int argc, char *argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
