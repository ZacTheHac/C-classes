using namespace std;
#include "stdafx.h"
#include "TCstring.h"


TCstring::TCstring(){
	SuperString.clear();
}
TCstring::~TCstring(){
}//array is automatically destroyed once it leaves scope, oddly. I expected to have to remove it myself, as I made it with new, but I suppose it's an actual variable.

TCstring::TCstring(const CHAR input[]){
	addChar(input);
}
TCstring::TCstring(const TCHAR input[]){
	addTChar(input);
}
TCstring::TCstring(const wstring input){
	addWString(input);
}
TCstring::TCstring(const string input){
	addString(input);
}


/*TCstring & TCstring::operator+(const CHAR input[]){
	TCstring toRet(*this);
	toRet.addChar(input);
	return toRet;
}
TCstring & TCstring::operator+(const TCHAR input[]){
	TCstring toRet(*this);
	toRet.addTChar(input);
	return toRet;
}
TCstring & TCstring::operator+(const wstring input){
	TCstring toRet(*this);
	toRet.addWString(input);
	return toRet;
}
TCstring & TCstring::operator+(const string input){
	TCstring toRet(*this);
	toRet.addString(input);
	return toRet;
}*/
TCstring & TCstring::operator+=(const CHAR input[]){
	addChar(input);
	return *this;
}
TCstring & TCstring::operator+=(const TCHAR input[]){
	addTChar(input);
	return *this;
}
TCstring & TCstring::operator+=(const wstring input){
	addWString(input);
	return *this;
}
TCstring & TCstring::operator+=(const string input){
	addString(input);
	return *this;
}
TCstring & TCstring::operator+=(const TCstring input){
	addTChar(input.getTCHAR());
	return *this;
}

TCstring & TCstring::operator=(const TCstring & input){
	SuperString.copy(input.SuperString);
	return *this;
}
TCstring & TCstring::operator=(const CHAR input[]){
	clear();
	addChar(input);
	return *this;
}
TCstring & TCstring::operator=(const TCHAR input[]){
	clear();
	addTChar(input);
	return *this;
}
TCstring & TCstring::operator=(const wstring input){
	clear();
	addWString(input);
	return *this;
}
TCstring & TCstring::operator=(const string input){
	clear();
	addString(input);
	return *this;
}

TCHAR & TCstring::operator[](int const index)const{
	TCHAR toRet = SuperString.getRecord(index+1);//since 0 is the start in here.
	return toRet;
}

bool TCstring::operator>(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if (result == -1)
		return true;
	else
		return false;
}
bool TCstring::operator>=(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if ((result == -1)||(result == 0))
		return true;
	else
		return false;
}
bool TCstring::operator<(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if ((result == 1))
		return true;
	else
		return false;
}
bool TCstring::operator<=(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if ((result == 1) || (result == 0))
		return true;
	else
		return false;
}
bool TCstring::operator==(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if ((result == 0))
		return true;
	else
		return false;
}
bool TCstring::operator!=(const TCstring comp)const{
	int result = compare(comp.SuperString, false);
	if ((result == 0))
		return false;//careful, this one is reverse from the others
	else
		return true;
}

int TCstring::compare(const TCstring input, bool caseSensitive)const{
	return compare(input.SuperString, caseSensitive);
}
int TCstring::compare(const CHAR input[], bool caseSensitive)const{
	return compare(TCstring(input), caseSensitive);//kinda cheating, but shut up?
}
int TCstring::compare(const TCHAR input[], bool caseSensitive)const{
	return compare(TCstring(input), caseSensitive);//kinda cheating, but shut up?
}
int TCstring::compare(const wstring input, bool caseSensitive)const{
	return compare(TCstring(input), caseSensitive);//kinda cheating, but shut up?
}
int TCstring::compare(const string input, bool caseSensitive)const{
	return compare(TCstring(input), caseSensitive);//kinda cheating, but shut up?
}

LPCWSTR TCstring::getLPCWSTR() const{
	LPCWSTR StrPoint = getTCHAR();
	return StrPoint;
}
TCHAR* TCstring::getTCHAR() const{
	int length = getLength();
	//delete[] array;
	TCHAR* array = new TCHAR[length+1];
	for (int i = 0; i < length; i++){
		array[i] = SuperString.getRecord(i + 1);
	}
	array[length] = NULL;//forgot I have to null terminate. it's been a looong time since that...
	return array;
}
wstring TCstring::getWString() const{
	wstring ws = getTCHAR();
	//ws.resize(getLength());
	return ws;
}
int TCstring::getLength() const{
	return SuperString.getLength();
}
int TCstring::max_size() const{
	return INT_MAX;
}
void TCstring::resize(int newSize, bool cutFrontNotEnd){
	if (newSize > getLength() || newSize < 0){
		return;
	}
	if (newSize == 0){
		clear();
	}
	else{
		int deletesize = getLength() - newSize;
		for (int i = 1; i <= deletesize; i++){
			if (cutFrontNotEnd){
				SuperString.deleteRecord(1);//cut the first one
			}
			else{
				SuperString.deleteRecord();//cut the last one
			}
		}
	}
}

void TCstring::clear(){
	SuperString.clear();
	//delete[] array;
}//deletes everything

bool TCstring::empty(){
	return SuperString.getLength() == 0;
}//checks IF it's empty.

void TCstring::addTChar(const TCHAR input[]){
	int counter = 0;
	TCHAR inp;
	while (true){
		inp = input[counter++];

		if (inp != NULL){
			SuperString.addRecord(inp);
		}
		else{
			break;
		}
	}
}
void TCstring::addChar(const CHAR input[]){
	int counter = 0;
	TCHAR inp;
	while (true){
		inp = input[counter++];

		if (inp != NULL){
			SuperString.addRecord(inp);
		}
		else{
			break;
		}
	}
	//yes, it's identical code. but I can't convert an entire array of char to tchar at once.
}
void TCstring::addWString(const wstring input){
	int length = input.size();
	for (int i = 0; i < length; i++)
	{
		SuperString.addRecord(input[i]);
	}
}
void TCstring::addString(const string input){
	int length = input.size();
	for (int i = 0; i < length; i++)
	{
		SuperString.addRecord(input[i]);
	}
	//again: identical code, but just because the functions overlap.
}

int TCstring::compare(LinkList<TCHAR> input, bool caseSensitive)const{
	int length;
	bool equalLength = false;
	if (getLength() < input.getLength()){
		length = getLength();
	}
	else if (getLength() == input.getLength()){
		length = getLength();
		equalLength = true;
	}
	else{
		length = input.getLength();
	}
	TCHAR SS, inp;
	for (int i = 1; i <= length; i++){
		SS = SuperString.getRecord(i);
		inp = input.getRecord(i);
		if(!caseSensitive){
			SS = towupper(SS);
			inp = towupper(inp);
		}
		
		if (SS == inp){
			continue;
		}
		else if (SS > inp){
			return -1;
		}
		else{
			return 1;
		}
	}
	if (equalLength)//it got out of the loop without determining a winner. so they're equal, as long as the length is equal
		return 0;
	else{//if the length is not equal, then the shorter one wins.
		if (length == getLength()){
			return -1;
		}
		else{
			return 1;
		}
	}
}
