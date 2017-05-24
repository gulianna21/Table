#pragma once
#include <iostream>

template<class KEY, class VAL>
class ViewTable
{
private:
	KEY* keys;
	VAL* values;
	size_t s;//size
	size_t used;

public:
	ViewTable(size_t size);
	~ViewTable();

	void add(KEY k,VAL v)
	{
		for (size_t i = 0; i < s; i++)
		{
			if (keys[i] == KEY() || arrKey[i] >= k)
			{
				keys[used] = k;
				values[used] = v;
				
				for (size_t x = i; i < used; i++)
				{
					KEY _k = arrKey[x];
					VAL _v = arrVal[x];

					arrKey[x] = arrKey[used];
					arrVal[x] = arrVal[used];
					arrKey[used] = _k;
					arrVal[used] = _v;
				}				
				used++;
				return;
			}
		}

		throw string("Table is full");
		
	}

	void remove(KEY k)
	{
		for (size_t i = 0; i < s; i++)
		{
			if (keys[i] == k)
			{
				for (size_t x = i; i < used; i++)
				{
					arrKey[x] = arrKey[used - 1];
					arrVal[x] = arrVal[used - 1];
				}
				arrKey[used--] = KEY();
				break;
			}
		}
	}

	VAL& operator[](KEY k)
	{
		for (size_t i = 0; i < s; i++)
			if (keys[i] == k)
				return values[i];
		
		throw string("Not found index");
	}

	ViewTable& operator = (ViewTable& vt)
	{
		s = vt.s;
		keys = new KEY[s];
		values = new VAL[s];
		used = vt.used;
		for (size_t i = 0; i < s; i++)
		{
			keys[i] = vt.keys[i];
			values[i] = vt.values[i];
		}

		return *this;
	}

	void resize(size_t newsized)
	{
		if (newsized == s)
			return;
		if (newsized < used)
			throw string("Need clear table");

		KEY defval = KEY();
		KEY* tmpk = new KEY[newsized];
		VAL* tmpv = new VAL[newsized];
		for (int i = 0; i < used; i++)
		{
			tmpk[i] = keys[i];
			tmpv[i] = values[i];
		}
		for (int i = used; i < newsized; i++)
		{
			tmpk[i] = KEY();
		}
		delete[]keys;
		delete[]values;
		keys = tmpk;
		values = tmpv;
		s = newsized;
	}

	
	friend std::ostream& operator<<(std::ostream& os, ViewTable& vt)
	{
		int width = 30+2;
		for (int i = 0; i < width+3; i++)
			os << "_";
		os << endl << "| KEYS";
		for (int i = 4; i < width/2; i++)
			os << " ";
		os << "| VALUES";
		for (int i = width / 2 +7; i < width; i++)
			os << " ";
		os << "|" << endl;
		KEY defval = KEY();
		for (size_t i = 0; i < vt.s; i++)
		{
			if (vt.keys[i] != defval)
			{
				os << "| "<< vt.keys[i];
				for (int iz = vt.keys[i].length(); iz < width / 2; iz++)
					os << " ";
				os << "| "<< vt.values[i];
				for (int iz = width / 2 + vt.values[i].length() +1; iz < width; iz++)
					os << " ";
				os << "|" << endl;
			}
		}
		os << "|";
		for (int i = 0; i < width+2; i++)
			os << "_" ;
		return os<<"|";
	}

};

template<class KEY, class VAL>
ViewTable<KEY,VAL>::ViewTable(size_t size)
{
	s = size;
	keys = new KEY[size];
	for (size_t i = 0; i < s; i++)
	{
		keys[i] = KEY();
	}
	values = new VAL[size];
	used = 0;
}

template<class KEY, class VAL>
ViewTable<KEY, VAL>::~ViewTable()
{
	delete[]keys;
	delete[]values;
}

