#pragma once
//everything is inline because templates misbehave. I spent a few hours trying to keep this in another file, and it would simply break silently, or break loudly.
//also: you don't realize how much you rely on intellisense until you accidentally crash it and have to code freehand. Bad habit, I should stop it. so many mis-spellings/miscapitalizations
template <class Type> class LinkList
{
public:
	LinkList()
	{
		length = 0;
		Start = nullptr;
		Latest = nullptr;
	}

	LinkList(const LinkList<Type>& other){
		copy(other);
	}

	void copy(const LinkList<Type>& toCopy){
		clear();

		int otherLength = toCopy.getLength();
		Type record;
		for (int i = 1; i <= otherLength; i++)
		{
			record = toCopy.getRecord(i);
			addRecord(record);
		}
	}

	LinkList & operator= (const LinkList<Type>& other){
		copy(other);
		return *this;
	}

	~LinkList(){
		clear();
	}

	Type getRecord(int recordNumber) const{
		element *RecElem = getElement(recordNumber);
		if (RecElem == nullptr){
			return NULL;
		}
		else{
			return RecElem->data;
		}
	}

	bool deleteRecord(int recordNumber = 0)
	{
		if (recordNumber == 0)
			recordNumber = length;//just like adding a record, removing w/o a param deletes the last

		if ((recordNumber > length) || recordNumber < 1){
			return false;
		}
		else if (Start == Latest){//they could only be destroying the beginning and end
			element *origStart = Start;
			delete origStart;
			Start = nullptr;
			Latest = nullptr;
		}
		else if (recordNumber == 1){
			element *origStart = Start;
			if (origStart->child){
				Start = origStart->child;
				if (Start)
					delete origStart;
			}
			else{
				Start = nullptr;
				length = 1;
			}
			//delete origStart;//memory management is important, but difficult. 
			//I can see why, as it gets more advanced, many companies absolutely suck at it. (no, my keyboard driver should NOT be sucking up 200MB of RAM)
		}
		else if (recordNumber == length){
			element *oldLast = Latest;
			Latest = getElement(length - 1);
			delete oldLast;
		}
		else{
			element *current = getElement(recordNumber - 1);
			element *elemToDelete = current->child;
			current->child = elemToDelete->child;
			delete elemToDelete;
		}
		length--;
		return true;
	}

	bool addRecord(Type data, int Slot = 0)//0 just means to the end of the list, as 1 is where the list starts
	{
		if ((Slot > (length + 1)) || Slot < 0){
			return false;//doesn't run the rest of the code, so I can use a single increment and return at the bottom.
		}

		element *newItem = new element;
		newItem->data = data;
		newItem->child = nullptr;
		if (Start == nullptr){//this can be first because the only legit values are 1 or 0, which are the same place, so it doesn't matter.
			Start = newItem;
			Latest = newItem;
		}
		else if (Slot == 0){
			Latest->child = newItem;
			Latest = newItem;
		}
		else if (Slot == 1){//put it at the start
			newItem->child = Start;
			Start = newItem;
		}
		else{//I sanitise the input before allowing it, so I don't need to do error checking here.
			element *current = getElement(Slot - 1);
			newItem->child = current->child;
			current->child = newItem;
		}
		length++;
		return true;
	}

	int getLength() const
	{
		return length;
	}

	void clear(){//erase everything
		int holder = getLength();
		for (int i = 1; i <= holder; i++){
			deleteRecord(1);
		}

		length = 0;
		Start = nullptr;
		Latest = nullptr;//just to make sure it's really dead
	}

private:
	struct element{
		Type data;
		element *child;
	};//probably better to make this its own class, but this is simpler, and if it ever becomes a problem I can move it

	element * getElement(int recordNumber)const{
		if (recordNumber > length){
			return nullptr;
		}
		int counter = 1;
		element *Current = Start;
		while (counter < recordNumber){
			Current = Current->child;
			counter++;
		}
		return Current;
	}

	element *Start;
	element *Latest;
	int length;//known flaw: this causes the linkedlist to break after a little over 2 billion records. so sad.
};
