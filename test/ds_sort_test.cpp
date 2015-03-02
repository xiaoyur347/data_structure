#include "gtest/gtest.h"
#include "../include/ds_vector.h"

namespace
{
using namespace data_structure;

template <typename TYPE>
void Swap(vector<TYPE> & vec, size_t i, size_t j)
{
	if (i == j)
	{
		return;
	}
	TYPE tmp;
	tmp = vec.at(i);
	vec.at(i) = vec.at(j);
	vec.at(j) = tmp;
}

template <typename TYPE>
void Swap(TYPE *vec, size_t i, size_t j)
{
	if (i == j)
	{
		return;
	}
	TYPE tmp;
	tmp = vec[i];
	vec[i] = vec[j];
	vec[j] = tmp;
}

void InitVector(vector<int> & vec)
{
	vec.push_back(9);
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(8);
	vec.push_back(3);
	vec.push_back(7);
	vec.push_back(4);
	vec.push_back(6);
	vec.push_back(2);
}

typedef void (*SortFunc)(vector<int> & vec);

// this is not bubble!
void BubbleSort1(vector<int> & vec)
{
	for (size_t i = 0; i < vec.size() - 1; ++i)
	{
		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			if (vec.at(j) < vec.at(i))
			{
				Swap(vec, i, j);
			}
		}
	}
}

// this is the bubble
void BubbleSort2(vector<int> & vec)
{
	for (size_t i = 0; i < vec.size() - 1; ++i)
	{
		for (size_t j = vec.size() - 1; j > i; --j)
		{
			if (vec.at(j) < vec.at(j-1))
			{
				Swap(vec, j-1, j);
			}
		}
	}
}

// this is the bubble extended
void BubbleSort3(vector<int> & vec)
{
	bool bSwap = true;
	for (size_t i = 0; bSwap && i < vec.size() - 1; ++i)
	{
		bSwap = false;
		for (size_t j = vec.size() - 1; j > i; --j)
		{
			if (vec.at(j) < vec.at(j-1))
			{
				Swap(vec, j-1, j);
				bSwap = true;
			}
		}
	}
}

// swap after loop
void SimpleSelectionSort(vector<int> & vec)
{
	for (size_t i = 0; i < vec.size() - 1; ++i)
	{
		size_t min_pos = i;
		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			if (vec.at(j) < vec.at(min_pos))
			{
				min_pos = j;
			}
		}
		//swap last
		if (min_pos != i)
		{
			Swap(vec, i, min_pos);
		}
	}
}

void InsertSort(vector<int> & vec)
{
	//first insert the data last, and the last one is i
	for (size_t i = 1; i < vec.size(); ++i)
	{
		// if the insert data < original data, judge the insert position
		// and move the data below
		if (vec.at(i) < vec.at(i-1))
		{
			int tmp = vec.at(i);
			size_t j = i;
			for (; j > 0 && vec.at(j-1) > tmp; --j)
			{
				vec.at(j) = vec.at(j-1);
			}
			vec.at(j) = tmp;
		}
	}
}

void ShellSort(vector<int> & vec)
{
	int increment = (int)vec.size();
	do
	{
		increment = increment / 3 + 1; // 3 is not easy to choose!
		for (size_t i = increment; i < vec.size(); ++i)
		{
			if (vec.at(i) < vec.at(i - increment))
			{
				int tmp = vec.at(i);
				int j = i - increment;
				for (; j >= 0 && vec.at(j) > tmp; j -= increment)
				{
					vec.at(j + increment) = vec.at(j);
				}
				vec.at(j + increment) = tmp;
			}
		}
	}
	while (increment > 1);
}

////////////////////////////////////////////////////////////////////////////////
//HeapSort
inline int get_parent(int child)
{
	return (child - 1) / 2;
}
inline int get_first_child(int parent)
{
	return parent * 2 + 1;
}
inline int get_sibling(int child)
{
	return child + 1;
}
void HeapAdjust(vector<int> & vec, int parent, int size)
{
	int parent_value = vec.at(parent);
	for (int child = get_first_child(parent); child < size; child = get_first_child(child))
	{
		// test if there is a sibling
		if (child < size - 1 && vec.at(child) < vec.at(get_sibling(child)))
		{
			child = get_sibling(child);
		}
		if (parent_value >= vec.at(child))
		{
			break;
		}
		vec.at(parent) = vec.at(child);
		parent = child;
	}
	
	vec.at(parent) = parent_value;
}

void HeapSort(vector<int> & vec)
{
	int i;
	int size = (int)vec.size();
	// create biggest-on-top heap
	for (i = get_parent(size - 1); i >= 0; --i)
	{
		HeapAdjust(vec, i, vec.size());
	}
	
	for (end = size - 1; end > 0; --end)
	{
		//move the biggest to the end
		Swap(vec, 0, end);
		HeapAdjust(vec, 0, end); // sort [0, end)
	}
}

////////////////////////////////////////////////////////////////////////////////
//MergeSort
//merge pIn[begin,mid) and pIn[mid, end) -> pOut[begin, end)
void Merge(int *pIn, int *pOut, int begin, int mid, int end)
{
	int left = begin;
	int right = mid;
	int index;
	for (index = begin; index < end; ++index)
	{
		if (left >= mid || right >= end)
		{
			break;
		}
		if (pIn[left] < pIn[right])
		{
			pOut[index] = pIn[left++];
		}
		else
		{
			pOut[index] = pIn[right++];
		}
	}
	if (left < mid)
	{
		//memcpy
		while (index < end)
		{
			pOut[index++] = pIn[left++];
		}
	}
	else if (right < end)
	{
		//memcpy
		while (index < end)
		{
			pOut[index++] = pIn[right++];
		}
	}
}

void MergePass(int *pIn, int *pOut, int step, int size)
{
	int begin = 0;
	//merge the first 2 * step ranges
	for (; begin + 2 * step <= size; begin += 2 * step)
	{
		Merge(pIn, pOut, begin, begin + step, begin + 2 * step);
	}
	
	//there are two ranges left, merge it
	if (begin < size - step)
	{
		Merge(pIn, pOut, begin, begin + step, size);
	}
	else
	{
		//there is only one range, copy it
		//memcpy
		for (; begin < size; ++begin)
		{
			pOut[begin] = pIn[begin];
		}
	}
}

void MergeSort(vector<int> &vec)
{
	if (vec.size() <= 1)
	{
		return;
	}
	int *pIn = &vec.at(0);
	int *pOut = new int[vec.size()];
	int size = (int)vec.size();
	
	for (int step = 1; step < size; )
	{
		MergePass(pIn, pOut, step, size);
		step *= 2;
		MergePass(pOut, pIn, step, size);
		step *= 2;
	}
	
	delete[] pOut;
}

////////////////////////////////////////////////////////////////////////////////
//QSort

int Partition(int *pInt, int first, int last)
{
	int pivotkey = pInt[first]; //there are lots of ways for pivot key
	while (first < last)
	{
		// if right >= pivot, move left
		for (;first < last && pInt[last] >= pivotkey;--last)
		{
		}
		Swap(pInt, first, last);
		// if left <= pivot, move right
		for (;first < last && pInt[first] <= pivotkey;++first)
		{
		}
		Swap(pInt, first, last);
	}
	
	return first;
}

// sort range [first, last]
void QSort(int *pInt, int first, int last)
{
	if (first < last)
	{
		int pivot = Partition(pInt, first, last);
		QSort(pInt, first, pivot - 1); // [first, pivot - 1]
		QSort(pInt, pivot + 1, last);  // [pivot + 1,  last]
	}
}

void QuickSort(vector<int> &vec)
{
	if (vec.size() <= 1)
	{
		return;
	}
	QSort(&vec.at(0), 0, int(vec.size()) - 1);
}

////////////////////////////////////////////////////////////////////////////////

TEST(sort, sort)
{
	SortFunc func[] = {
		BubbleSort1, 
		BubbleSort2, 
		BubbleSort3,
		SimpleSelectionSort,
		InsertSort,
		ShellSort,
		HeapSort,
		MergeSort,
		QuickSort
	};
	for (unsigned round = 0; round < sizeof(func)/sizeof(func[0]); ++round)
	{
		vector<int> vec;
		InitVector(vec);
		(*func[round])(vec);
		printf("[%d]", round);
		for (size_t i = 0; i < vec.size(); ++i)
		{
			printf("%d,", vec.at(i));
		}
		printf("\n");
		for (size_t i = 0; i < vec.size(); ++i)
		{
			ASSERT_EQ(int(i + 1), vec.at(i)) << "round" << round;
		}
	}
}

}