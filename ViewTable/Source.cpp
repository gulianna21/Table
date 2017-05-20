#include <iostream>
#include <string>
#include "ViewTable.h"

using namespace std;

void main()
{
	ViewTable<string,string> vt(15);

	try {
		vt.add("in", "ti");
		vt.add("ind", "val3");
		vt.add("test", "test2");

		cout << vt["in"] << endl;
		cout << vt["test"] << endl;
		cout << vt["ind"] << endl;

		vt.resize(20);
	}
	catch (string s)
	{
		cout << "error: " << s << endl;
	}

	cout << vt;

	cin.get();
}