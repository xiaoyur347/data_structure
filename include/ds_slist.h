#ifndef DATA_STRUCTURE_SLIST_H
#define DATA_STRUCTURE_SLIST_H

#include <stdlib.h> // for NULL define
#include <bits/functexcept.h>

namespace data_structure
{
template<typename TYPE>
class slist
{
public:
	typedef struct item
	{
		item* next;
		TYPE data;
	}item;
	typedef item* pointer;
	typedef const item* const_pointer;
	slist()
	{
		_M_head = new item;
		_M_head->next = NULL;
	}
	~slist()
	{
		clear();
		delete _M_head;
		_M_head = NULL;
	}
	size_t size() const
	{
		size_t i = 0;
		for (pointer pCur = _M_head->next; pCur != NULL; pCur = pCur->next)
		{
			++i;
		}
		
		return i;
	}
	bool empty() const
	{
		return _M_head->next == NULL;
	}
	void clear()
	{
		pointer pCur = _M_head->next;
		_M_head->next = NULL;
		
		while (pCur != NULL)
		{
			pointer pNext = pCur->next;
			delete pCur;
			pCur = pNext;
		}
	}
	TYPE& at(size_t loc)
	{
		size_t i = 0;
		for (pointer pCur = _M_head->next; pCur != NULL; pCur = pCur->next)
		{
			if (i == loc)
			{
				return pCur->data;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
	const TYPE& at(size_t loc) const
	{
		size_t i = 0;
		for (const_pointer pCur = _M_head->next; pCur != NULL; pCur = pCur->next)
		{
			if (i == loc)
			{
				return pCur->data;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
	void push_back(const TYPE& val)
	{
		pointer pLast = _M_head;
		for (; pLast->next != NULL; pLast = pLast->next)
		{
		}
		
		pointer pCur = new item;
		pCur->data = val;
		pCur->next = NULL;
		pLast->next = pCur;
	}
	void push_front(const TYPE& val)
	{
		pointer pCur = new item;
		pCur->data = val;
		pCur->next = _M_head->next;
		_M_head->next = pCur;
	}
	void insert(size_t loc, const TYPE& val)
	{
		pointer pLast = _M_head;
		size_t i = 0;
		for (; pLast->next != NULL; pLast = pLast->next)
		{
			if (i == loc)
			{
				break;
			}
			++i;
		}
		
		if (i < loc)
		{
			std::__throw_out_of_range(__N("slist::_M_range_check"));
		}
		
		pointer pCur = new item;
		pCur->data = val;
		pCur->next = pLast->next;
		pLast->next = pCur;
	}
	void remove(size_t loc)
	{
		pointer pLast = _M_head;
		size_t i = 0;
		for (; pLast->next != NULL; pLast = pLast->next)
		{
			if (i == loc)
			{
				pointer pNext = pLast->next->next;
				delete pLast->next;
				pLast->next = pNext;
				return;
			}
			++i;
		}
		
		std::__throw_out_of_range(__N("slist::_M_range_check"));
	}
private:
	pointer _M_head;
};

} // namespace data_structure

#endif
