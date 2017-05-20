#pragma once
#include <iostream>

template<class KEY, class VAL>
class ViewTable
{
private:
	KEY* keys;
	VAL* values;
	size_t s;//size
	size_t used;//количество используемых эл

public:
	ViewTable(size_t size);
	~ViewTable();

	void add(KEY k,VAL v)
	{
		for (size_t i = 0; i < s; i++)
		{
			if (keys[i] == KEY())
			{
				keys[i] = k;
				values[i] = v;
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
				used--;
				keys[i] = KEY();
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

		KEY defval = KEY();//значение по умолчанию
		KEY* tmpk = new KEY[newsized];
		VAL* tmpv = new VAL[newsized];
		size_t insertindex = 0;
		for (int i = 0; i < s; i++)
		{
			if (keys[i] != defval)
			{
				tmpk[insertindex] = keys[i];
				tmpv[insertindex] = values[i];
				++insertindex;
			}
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

