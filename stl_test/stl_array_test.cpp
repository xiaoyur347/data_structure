#include "gtest/gtest.h"
#include <array>
#include <stdio.h>

namespace
{

TEST(array, init)
{
	std::array<int, 10> arr;
	
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;
	
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		printf("%d,", *it);
	}
	printf("\n");
	
	printf("front=%d,back=%d\n", arr.front(), arr.back());
}

} // namespace
