#ifndef DATA_STRUCTURE_VECTOR_H
#define DATA_STRUCTURE_VECTOR_H

#include <stdlib.h> // for NULL define
#include <bits/functexcept.h>

namespace data_structure
{
template<typename TYPE>
class vector
{
public:
	static const size_t min_size = 4;
	typedef TYPE* pointer;
	vector()
		:_M_start(NULL),
		 _M_finish(NULL),
		 _M_end_of_storage(NULL)
	{
	}
	~vector()
	{
		if (_M_start != NULL)
		{
			delete []_M_start;
		}
		_M_start = NULL;
	}
	size_t size() const
	{
		return _M_finish - _M_start;
	}
	size_t capacity() const
	{
		return _M_end_of_storage - _M_start;
	}
	bool empty() const
	{
		return (_M_finish - _M_start) == 0;
	}
	void clear()
	{
		_M_finish = _M_start;
	}
	TYPE& at(size_t loc)
	{
		if (loc >= size())
		{
			std::__throw_out_of_range(__N("vector::_M_range_check"));
		}
		
		return *(_M_start + loc);
	}
	const TYPE& at(size_t loc) const
	{
		if (loc >= size())
		{
			std::__throw_out_of_range(__N("vector::_M_range_check"));
		}
		
		return *(_M_start + loc);
	}
	void push_back(const TYPE& val)
	{
		_reserve();
		
		*_M_finish = val;
		++_M_finish;
	}
	// STL vector insert uses iterator as loc
	void insert(size_t loc, const TYPE& val)
	{
		if (loc > size())
		{
			std::__throw_out_of_range(__N("vector::_M_range_check"));
		}
		
		_reserve();
		
		pointer pSrc;
		for (pSrc = _M_finish; pSrc > _M_start + loc; --pSrc)
		{
			*pSrc = *(pSrc - 1);
		}
		*pSrc = val;
		++_M_finish;
	}
	void remove(size_t loc)
	{
		if (loc >= size())
		{
			std::__throw_out_of_range(__N("vector::_M_range_check"));
		}
		
		pointer pSrc;
		for (pSrc = _M_start + loc; pSrc < _M_finish - 1; ++pSrc)
		{
			*pSrc = *(pSrc + 1);
		}
		--_M_finish;
	}
	void reserve(size_t s)
	{
		pointer pNew = new TYPE[s];
		if (_M_start != NULL)
		{
			pointer pDst = pNew;
			for (pointer pSrc = _M_start; pSrc != _M_finish; )
			{
				*pDst++ = *pSrc++;
			}
		}
		_M_finish = pNew + size();
		delete []_M_start;
		_M_start = pNew;
		_M_end_of_storage = _M_start + s;
	}
private:
	void _reserve()
	{
		if (_M_end_of_storage == _M_finish)
		{
			//new space
			if (_M_start == NULL)
			{
				reserve(min_size);
			}
			else
			{
				reserve(capacity() * 2);
			}
		}
	}
	pointer _M_start;
	pointer _M_finish;
	pointer _M_end_of_storage;
};

} // namespace data_structure

#endif
