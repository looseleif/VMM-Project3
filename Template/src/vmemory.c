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
	//printf("cr3: %p\n", cr3[1]);

	// You can add other initialization here as necessary

	/*int i;
	int j;
	int counter1 = 1;
	int counter2 = 1;

	int doubleCheck = 0;
	int dubCount = 0 ;

	for(i=0; i <  1023; i++){

		if(cr3[i]!=NULL){ 
			//counter1++;
			printf("pointer: %p\n", cr3[i]);
			
			for(j = 0; j < 1023; j++){
			
			if(cr3[i][j]!=-1){
				printf("value: %x\n", cr3[i][j]);

				//printf("c1:%d\n", i);
				//printf("c2:%d\n", j);

				counter2++;

				if(doubleCheck){

				printf("double found at: %d\n",counter1);
				dubCount++;
				}

				doubleCheck = 1;
				}


			
			}

			doubleCheck = 0;

		}

	}

	//printf("c1:%d\n", counter1);
	printf("c2:%d\n", counter2);
	printf("dub:%d\n", dubCount);

	//FILE* output;

    //int V_addrs = fopen("../bin/virtual.txt", "a");
	*/
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
