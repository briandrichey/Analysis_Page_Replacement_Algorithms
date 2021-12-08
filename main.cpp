// Remember to add comments to your code

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "pagetable.h"

// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x)
{
	/* First x in the below expression is for the case when x is 0 */
	return x && (!(x & (x - 1)));
}

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "=================================================================" << std::endl;
	std::cout << "CS 433 Programming assignment 5" << std::endl;
	std::cout << "Authors: Jake Tremblay, Danny Ha, Brian Richie" << std::endl;
	std::cout << "Date: 12/1/2021" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
	std::cout << "=================================================================\n" << std::endl;

	if (argc < 3) {
		// user does not enter enough parameters
		std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
			<< "two command-line arguments:" << std::endl
			<< " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
			<< " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
		exit(1);
	}

	// Page size and Physical memory size 
	// Their values should be read from command-line arguments, and always a power of 2
	unsigned int page_size = atoi(argv[1]);

	if (!isPowerOfTwo(page_size)){
		std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
			<< "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
		return 1;
	}

	unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
	if (!isPowerOfTwo(phys_mem_size)){
		std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
			<< "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
		return 1;
	}

	// calculate number of pages and frames;
	int logic_mem_bits = 27;		// 27-bit logical memory (128 MB logical memory assumed by the assignment)
	int phys_mem_bits = std::log2(phys_mem_size);		// Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
	int page_offset_bits = std::log2(page_size);				// Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
	// Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
	int num_pages = 1 << (logic_mem_bits - page_offset_bits);
	// Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
	int num_frames = 1 << (phys_mem_bits - page_offset_bits);

	std::cout << "Page size = " << page_size << " bytes" << std::endl;
	std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
	std::cout << "Number of pages = " << num_pages << std::endl;
	std::cout << "Number of physical frames = " << num_frames << std::endl;
	
	PageTable ourTable;
	ourTable.init(num_pages);			//creates 'num_pages' amount of PageEntry into pageTable vector (-1, false, false) are starting values
	
	// Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
	std::cout << "\n================================Test 1==================================================\n";
	// TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address

	std::ifstream smallFile;
	smallFile.open("small_refs.txt", std::ios::in);
	if (!smallFile) {
		std::cout << "Error in file creation." << std::endl;
	}
	else {
		int input, frame = 0, pageFaults = 0, pageCount = 0, pageReplacements = 0;

		while (smallFile.eof() == false) {								//go through small reference file until end
			smallFile >> input;
			int pageNum = input / page_size;
			++pageCount;												//count up the references we get through

			PageEntry temp(frame, false, false);						//create a new page entry using frame # we are currently on
			

			if (ourTable.pageTable2.find(pageNum) != ourTable.pageTable2.end()) {		//if the page table's map finds the element
				auto it = ourTable.pageTable2.find(pageNum);
				PageEntry target = it->second;
				target.dirty = false;
				std::cout << "Logical Memory address: " << input << " Page Number: " << pageNum << " Frame Number: " << target.frame_num << " Page Fault?: " << target.dirty << std::endl;
			}
			else if(!(ourTable.pageTable2.size() > num_pages)){							//if the page is not found in the table, and the tables size is not greater than number of pages
				frame++;											//we only insert into a new frame if we actually have to insert, i believe
				pageFaults++;										//if we dont find the page in the map, page fault + 1
				temp.dirty = true;									//set dirty bit to true so we know this has generated page fault
				ourTable.pageTable2.emplace(pageNum, temp);				//ourTable is the page table, pageTable2 is a map<int pageNum, PageEntry>
				std::cout << "Logical Memory address: " << input << " Page Number: " << pageNum << " Frame Number: " << temp.frame_num << " Page Fault?: " << temp.dirty << std::endl;
			}
			else {
				pageReplacements++;									//the small ref will never hit this line
			}
		}
		smallFile.close();

		
		std::cout << "Number of references: " << pageCount << std::endl;
		std::cout << "Number of page faults: " << pageFaults << std::endl;
		std::cout << "Number of page replacements: " << pageReplacements << std::endl;
	}
	



	// Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
	std::cout << "\n================================Test 2==================================================\n";

	std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using FIFO replacement algorithm	
	// TODO: print the statistics and run-time

	std::ifstream largeFile;
	largeFile.open("large_refs.txt", std::ios::in);
	if (!largeFile) {
		std::cout << "Error in file creation." << std::endl;
	}
	else {
		
		int input, frame = 0, pageFaults = 0, pageCount = 0, pageReplacements = 0;
		//timer start
		while (largeFile.eof() == false) {
			largeFile >> input;
			int pageNum = input / page_size;
			++pageCount;
		}
		//timer end
	}

	std::cout << "****************Simulate Random replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using Random replacement algorithm
	// TODO: print the statistics and run-time

	std::cout << "****************Simulate LRU replacement****************************" << std::endl;
	// TODO: Add your code to calculate number of page faults using LRU replacement algorithm
	// TODO: print the statistics and run-time

}
