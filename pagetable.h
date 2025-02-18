#pragma once

#include <vector>

//page table entry
class PageEntry{
public:
	int frame_num;				// Physical frame number for a given page
	bool valid = false;			// valid bit represents whether a page is in the physical memory
	bool dirty = false;			// dirty bit represents whether a page is changed
	
	PageEntry();
	PageEntry(int f, bool v, bool d);	//constructor for page elements using (frame_num, valid, dirty) as parameters
};


/**
 * A page table is like an array of page entries. The size of the page table should equal to the number of pages in logical memory
 */
class PageTable{
public:
	std::vector<PageEntry> pageTable;
	int tableSize;				//number of elements in table
	int pageSize;				//size of pages (in mb?)
	int memorySize;				//size of memory (in mb?)

	PageTable();				//constructor
private:
};
