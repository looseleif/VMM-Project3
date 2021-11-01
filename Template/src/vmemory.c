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

int offset;
int first_addr;
int second_addr;
int pt2_ptr;
unsigned int pt1_ptr;

int TLB[8][2];

int count_TLB = 0;

// TLB[x][0] is the VA
// TLB[x][1] is the PA


// The implementation of get_vpage_cr3 is provided in 
// an object file, so no need to re-implement it

void initialize_vmanager(int policy) 
{
	// Set LFU policy when passed as a parameter
	if (policy)
		FIFO_policy = false;
	// Set base pointer to page table
	cr3 = get_vpage_cr3();
	//printf("cr3: %p\n", cr3[1]);

	// You can add other initialization here as necessary

	//printf("c1:%d\n", counter1);

	//FILE* output;

    //int V_addrs = fopen("../bin/virtual.txt", "a");

}

//
// The implementation of the following functions is required
//

int translate_virtual_address(unsigned int v_addr)
{
	//TODO

	int offset;

	offset = v_addr & 0b00000000000000000000111111111111;
	pt2_ptr = v_addr & 0b00000000001111111111000000000000;
	pt2_ptr = pt2_ptr >> 12;
	pt1_ptr = v_addr & 0b11111111110000000000000000000000;
	pt1_ptr = pt1_ptr >> 22;


	//printf("num: %x\n", v_addr);
	//printf("offset: %x\n", offset);
	//printf("pt2: %d\n", pt2_ptr);
	//printf("pt1: %d\n", pt1_ptr);

	unsigned int result = 0;

	//printf("value 2 retrieve: %x\n", cr3[pt1_ptr][pt2_ptr]);

	if(cr3[pt1_ptr] != NULL){

		result = cr3[pt1_ptr][pt2_ptr];

		if(result != -1){

			return result;

		}

	}

	return -1;
	
}

void print_physical_address(int frame, int offset)
{
	
	unsigned int output = 0;
	unsigned int temp;

	output = (frame<<12) | (offset);

	

	int count = 0;

	temp = output;

	while(temp>0){

		temp = temp / 16;
		count++;
		
		//printf("translated step address: %x\n", output);

	}

	printf("0x");

	int i;

	for (i = 0; i < 8-count; i++)
	{
		printf("0");
	}

	printf("%x\n", output);

	return;

}

int get_tlb_entry(int n)
{
	
	if(TLB[n][1] != -1){

		return TLB[n][1];

	}

	return -1;

}

void populate_tlb(int v_addr, int p_addr) 
{
	//TODO
	
	int counter;

	int num = v_addr & 0b11111111111111111111000000000000;

	// first input comes in the 

	if(count_TLB==8){ // given TLB is full;

		for(counter=7; counter>0; counter--){

			TLB[counter][0] = TLB[counter-1][0];
			TLB[counter][1] = TLB[counter-1][1];

		}

		TLB[0][0] = num;
		TLB[0][1] = p_addr;

	} else {

		TLB[7-count_TLB][0] = num;
		TLB[7-count_TLB][1] = p_addr;

		count_TLB++;

	}

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
