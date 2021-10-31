//Implement the API modeling the translation of virtual page address to a
//physical frame address. We assume a 32 bit virtual memory and physical memory.
//Access to the page table is only via the CR3 register.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vmemory.h"

#define OUT_TLB "../bin/tlb_out.txt"
#define VIR_ADDR "../bin/virtual.txt"

#define FST_PT "../bin/first_pt.txt"
#define SEC_PT "../bin/second_pt.txt"

bool FIFO_policy = true;
int **cr3;
//
// You can declare global variables necessary for your TLB implementation here
//

int offset;
int first_addr;
int second_addr;
int pt2_ptr;
unsigned int pt1_ptr;

//
// More static helper functions can be implemented here
//


// The implementation of get_vpage_cr3 is provided in 
// an object file, so no need to re-implement it
void initialize_vmanager(int policy) 
{
	// Set LFU policy when passed as a parameter
	if (policy)
		FIFO_policy = false;
	// Set base pointer to page table
	cr3 = get_vpage_cr3();
	printf("cr3: %p\n", cr3[1]);

	// You can add other initialization here as necessary

	//FILE* output;

    //int V_addrs = fopen("../bin/virtual.txt", "a");

}

//
// The implementation of the following functions is required
//
int translate_virtual_address(unsigned int v_addr)
{
	//TODO Ex. "0x82e2e665"

	int offset;

	offset = v_addr & 0b00000000000000000000111111111111;
	pt2_ptr = v_addr & 0b00000000001111111111000000000000;
	pt2_ptr = pt2_ptr >> 12;
	pt1_ptr = v_addr & 0b11111111110000000000000000000000;
	pt1_ptr = pt1_ptr >> 22;


	printf("num: %x\n", v_addr);
	printf("offset: %x\n", offset);
	printf("pt2: %d\n", pt2_ptr);
	printf("pt1: %d\n", pt1_ptr);

	return -1;
}

void print_physical_address(int frame, int offset)
{
	//TODO
	return;
}

int get_tlb_entry(int n)
{
	//TODO
	return -1;
}

void populate_tlb(int v_addr, int p_addr) 
{
	//TODO
	return;
}

float get_hit_ratio()
{
	//TODO
	return 0.0;
}

// Write to the file denoted by OUT_TLB
void print_tlb()
{
	//TODO
	return;
}
