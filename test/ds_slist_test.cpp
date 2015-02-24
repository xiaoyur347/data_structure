#include "gtest/gtest.h"
#include "../include/ds_slist.h"

namespace
{

using namespace data_structure;
TEST(slist, push_back)
{
	slist<int> vec;
	ASSERT_TRUE(vec.empty());
	
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	
	ASSERT_FALSE(vec.empty());
	ASSERT_EQ(5U, vec.size());
	for (size_t i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(int(i + 1), vec.at(i));
	}
}

TEST(slist, insert_head)
{
	slist<int> vec;
	
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	
	vec.insert(0, 10);
	ASSERT_EQ(10, vec.at(0));
	for (size_t i = 1; i < vec.size(); ++i)
	{
		ASSERT_EQ(int(i), vec.at(i));
	}
	
	vec.remove(0);
	for (size_t i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(int(i + 1), vec.at(i));
	}
}

TEST(slist, insert_tail)
{
	slist<int> vec;
	
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	
	vec.insert(5, 10);
	ASSERT_EQ(10, vec.at(5));
	for (size_t i = 0; i < vec.size() - 1; ++i)
	{
		ASSERT_EQ(int(i + 1), vec.at(i));
	}
	
	vec.remove(5);
	for (size_t i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(int(i + 1), vec.at(i));
	}
}

TEST(slist, insert_mid)
{
	slist<int> vec;
	
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	
	vec.insert(3, 10);
	ASSERT_EQ(10, vec.at(3));
	ASSERT_EQ(1, vec.at(0));
	ASSERT_EQ(2, vec.at(1));
	ASSERT_EQ(3, vec.at(2));
	ASSERT_EQ(4, vec.at(4));
	ASSERT_EQ(5, vec.at(5));
	
	vec.remove(3);
	for (size_t i = 0; i < vec.size(); ++i)
	{
		ASSERT_EQ(int(i + 1), vec.at(i));
	}
}

}