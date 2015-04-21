#pragma once
#include "LinkList.h"
#include "tchar.h"
#include "string.h"


class TCstring
{
public:
	TCstring();
	TCstring(const CHAR input[]);
	TCstring(const TCHAR input[]);
	TCstring(const wstring input);
	TCstring(const string input);
	~TCstring();
	/*TCstring & operator+(const CHAR input[]);
	TCstring & operator+(const TCHAR input[]);
	TCstring & operator+(const wstring input);
	TCstring & operator+(const string input);I cant get these to work right. may revisit.*/
	TCstring & operator+=(const CHAR input[]);
	TCstring & operator+=(const TCHAR input[]);
	TCstring & operator+=(const wstring input);
	TCstring & operator+=(const string input);
	TCstring & operator+=(const TCstring input);
	TCstring & operator=(const TCstring & input);
	TCHAR & operator[](const int index)const;
	bool operator>(const TCstring compare)const;
	bool operator>=(const TCstring compare)const;
	bool operator<(const TCstring compare)const;
	bool operator<=(const TCstring compare)const;
	bool operator==(const TCstring compare)const;
	bool operator!=(const TCstring compare)const;//warning: all comparisons do a case-insensitive search by default. use the compare functions if you need case-sensitive
	int compare(const TCstring input, bool caseSensitive = false)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger
	int compare(const CHAR input[], bool caseSensitive = false)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger
	int compare(const TCHAR input[], bool caseSensitive = false)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger
	int compare(const wstring input, bool caseSensitive = false)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger
	int compare(const string input, bool caseSensitive = false)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger
	LPCWSTR getLPCWSTR() const;
	TCHAR* getTCHAR() const;
	wstring getWString() const;
	int getLength() const;
	int max_size() const;
	void resize(int newSize, bool cutFrontNotEnd = false);
	void clear();//deletes everything
	bool empty();//checks IF it's empty. so, the opposite of LL.
private:
	//hmmm I wonder how I'm going to store this. I could make an array that I copy to a new one once space runs out... or...
	LinkList<TCHAR> SuperString;//I love my LL class.
	//TCHAR* array;
	void addTChar(const TCHAR input[]);
	void addChar(const CHAR input[]);
	void addWString(const wstring input);
	void addString(const string input);
	int compare(LinkList<TCHAR> input, bool caseSensitive)const;//0 means they're equal, -1 means this one is bigger, 1 means the input is bigger

};

