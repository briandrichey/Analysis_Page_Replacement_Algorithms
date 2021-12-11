#pragma once

#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>


//page table entry
class PageEntry{
public:
	int page_addr;				// Actual page number that gets calculated
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
	std::vector<PageEntry> pageVector;
	std::queue<PageEntry> pageQueue;
	std::unordered_map<int, PageEntry> pageMap;
	std::deque<int> pageDeque;


	int tableSize;				//number of elements in table
	int pageSize;				//size of pages (in mb?)
	int memorySize;				//size of memory (in mb?)

	PageTable();				//constructor
	PageTable(int tSize, int pSize, int mSize);

	void init(int size);

	
private:
};
