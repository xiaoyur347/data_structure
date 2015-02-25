#include "gtest/gtest.h"
#include "../include/ds_queue.h"

namespace
{

using namespace data_structure;
TEST(queue, common)
{
	queue<int> data;
	ASSERT_TRUE(data.empty());
	
	data.push(1);
	data.push(2);
	data.push(3);
	data.push(4);
	data.push(5);
	
	ASSERT_FALSE(data.empty());
	ASSERT_EQ(5U, data.size());
	ASSERT_EQ(1, data.front());
	data.pop();
	ASSERT_EQ(2, data.front());
	data.pop();
	ASSERT_EQ(3, data.front());
	data.pop();
	ASSERT_EQ(4, data.front());
	data.pop();
	ASSERT_EQ(5, data.front());
	data.pop();
}

}