#include "pagetable.h"

PageEntry::PageEntry() {			//default const
	frame_num = 0;
	//valid = false, dirty = false
}

//parameterized constructor, (frame_num, valid bit, dirty bit)
PageEntry::PageEntry(int f, bool v, bool d) {
	frame_num = f;
	valid = v;
	dirty = d;
}

PageTable::PageTable(){
	tableSize = 0;
	pageSize = 0;
	memorySize = 0;
}

PageTable::PageTable(int tSize, int pSize, int mSize){
	tableSize = tSize;
	pageSize = pSize;
	memorySize = mSize;
}

//this is only really for the vector 
void PageTable::init(int size){
	for (int i = 0; i < size; i++) {
		PageEntry newEntry;
		newEntry.frame_num = -1;
		newEntry.dirty = false;
		newEntry.valid = false;

		pageVector.push_back(newEntry);
	}
}

