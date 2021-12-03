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

