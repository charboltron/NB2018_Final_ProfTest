// Copyright (c) 2018 Jason Graalum
//
// 
// MemList.cpp
//
// // Class implementation of MemList for New Beginnings Final Proficiency Exam
// 2018

#include "MemList.hpp"
#include "MemBlock.hpp"
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////
// Level 0 Methods
/////////////////////////////////////////////////////////////////////////////////
// Default constructor which creates empty lists for both the Free and Reserved
// lists
//
// Level 0
//
MemList::MemList()
{
    free_head = NULL;
    reserved_head = NULL;
}
// Display the Free List
//
// Level 0
//
void MemList::displayFree() 
{
    std::cout << "Free Memory" << std::endl;
    MemBlock * current = free_head;
    free_head->printBlockInfoHeader();
    int count = 0;
    while(current) {
        current->printBlockInfo(count);
        current = current->getNext();
        count++;
    }
    std::cout << std::endl;
}

// Display the Reserved List
//
// Level 0
//
void MemList::displayReserved() 
{
    std::cout << "Reserved Memory" << std::endl;
    MemBlock * current = reserved_head;
    reserved_head->printBlockInfoHeader();

    int count = 0;
    while(current) {
        current->printBlockInfo(count);
        current = current->getNext();
        count++;
    }
    std::cout << std::endl;

}
/////////////////////////////////////////////////////////////////////////////////
// Level 1 Methods
/////////////////////////////////////////////////////////////////////////////////
// Parameterized constructor which create two lists of MemBlock 
// The Free List will contain a single MemBlock with all the memory(start_addr and mem_size)
// The Reserved List will be empty
//
// MemList = new MemList(start_addr, mem_size);
//
// Level 1
//
MemList::MemList(unsigned int s_addr, unsigned int block_size)
{
    // To be implemented(replace the two lines below)

    free_head = new MemBlock(s_addr, block_size);
    //free_head->setNext(NULL);	
    
    reserved_head = NULL;
    
}

// Find the first MemBlock in the Free list which is greater than or equal to the amount requested(via 
// the function argument). Update the MemBlock in the Free List - change the start_addr and mem_size
// by the amount of memory being reserved.


// Add the newly reserved memory into a new MemBlock in the Reserved List
// If no MemBlock in the Free List is large enough return NULL, otherwise return a pointer to 
// the new MemBlock in the Reserved List.
//
// Level 1
//
MemBlock * MemList::reserveMemBlock(unsigned int block_size)
{
    // To be implemented
	
    MemBlock * current = free_head; 
    MemBlock * new_reserved = new MemBlock;
 
    new_reserved->setNext(reserved_head);	
    reserved_head = new_reserved;  

    bool found = false; 

	  if (block_size <= current->getSize()) {found = true;}

	while(current->getSize() < block_size && current->getNext() != NULL && !found) {
		
		current = current->getNext();
		if (block_size <= current->getSize()) {found = true;}
		}
	if(!found) {return NULL;}

	else{
	
	new_reserved->setAddr(current->getAddr());
	current->setAddr(current->getAddr() + block_size);                                
	current->setSize(current->getSize() - block_size);
	new_reserved->setSize(block_size);	     
	
		}
    return new_reserved;
}


// Return the total size of all blocks in the Reserved List
//
// Level 1
//
unsigned int MemList::reservedSize()
{
    // To be implemented

    MemBlock * current = reserved_head; 
    unsigned int sum = 0;	

 	while(current != NULL) { 
	
		sum += current->getSize();
		current = current->getNext();
	}
	
    return sum;
}

// Return the total size of all blocks in the Free List
//
// Level 1
unsigned int MemList::freeSize()
{
    // To be implemented

    MemBlock * current = free_head;
    unsigned int sum = 0; 

	while(current != NULL) {
	
		sum += current->getSize();
		current = current->getNext();
	}


    return sum;
}

/////////////////////////////////////////////////////////////////////////////////
// Level 2 Methods
/////////////////////////////////////////////////////////////////////////////////
// Removes the MemBlock provided(via the pointer) from the Reserved List and adds it
// back into the Free List - it must be added back "in order of starting address".
//
// (Challenge) If the MemBlock to be freed doesn't exist or it is a bad block(it overlaps 
// with a block in the Free list), return false.  Otherwise return true.
//
// Level 2
//
bool MemList::freeMemBlock(MemBlock * block_to_free)
{
    // To be implemented

	if (block_to_free != reserved_head) {

	MemBlock * current1 = reserved_head;

	while(current1 != NULL && current1->getNext() != NULL && current1->getNext() != block_to_free) {
	
		current1 = current1->getNext();
		}
	current1->setNext(block_to_free->getNext()); 
	}
		
	else {reserved_head->setNext(block_to_free->getNext());}


	if(block_to_free->getAddr() < free_head->getAddr()) {

		block_to_free->setNext(free_head);
		free_head = block_to_free;
	}
		
	else {  MemBlock * current = free_head;
		
		while (current!= NULL && current->getNext() != NULL && block_to_free->getAddr() > current->getNext()->getAddr()) {
		
			current = current->getNext();
			}
	
		block_to_free->setNext(current->getNext());
		current->setNext(block_to_free);
		}
    return true;
}



// Return a pointer to the MemBlcok with the largest size from the Free List
//
// Level 2
//
MemBlock * MemList::maxFree() 
{
    // To be implemented

    MemBlock * current = free_head;

    unsigned int max = 0; 

	while(current->getNext() != NULL) {

		if (current->getSize() > max) { max = current->getSize();}
		current = current->getNext();
	}
	current = free_head;

	while(current->getNext() != NULL) {
		
		if(current->getSize() == max) {return current;}
		else current = current->getNext();
	}
	
    return NULL;
}

// Return a pointer to the MemBlcok with the smallest size from the Free List
//
// Level 2
//
MemBlock * MemList::minFree()
{
    // To be implemented

    MemBlock * current = free_head;

    unsigned int min = current->getSize();

        while(current->getNext() != NULL) {

                if (current->getSize() < min) { min = current->getSize();}
                current = current->getNext();
        }
        current = free_head;

        while(current->getNext() != NULL) {

                if(current->getSize() == min) {return current;}
                else current = current->getNext();
        }
	
	
    return NULL;
}

// Return the number of MemBlocks in the Free List
//
// Level 2
//
unsigned int MemList::freeBlockCount()
{
    // To be implemented

    MemBlock * current = free_head;
    unsigned int counter = 0;

	while (current != NULL) { 
		counter++;
		current = current->getNext();
		}	
		
    return counter;
}

/////////////////////////////////////////////////////////////////////////////////
// Level 3 Methods
/////////////////////////////////////////////////////////////////////////////////
// Iterate through the Free List - combine any blocks that are adjacent
// Return the number of MemBlocks removed
//
// Level 3
//
unsigned int MemList::defragFree()
{
    // To be implemented
    return 0;
}

// Return the start address of the smallest block that fits the size requested
// Ex:  MemList_Obj->minMax(100);  // Return the address of the smallest block 
//                                    that is greater than 100
// The return values are the same as in the "reserveMemBlock" member function.
//
// Level 3
//
MemBlock * MemList::reserveMinMemBlock(unsigned int)
{
    // To be implemented
    return NULL;
}




