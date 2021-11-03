//Implement the API modeling the translation of virtual page address to a
//physical frame address. We assume a 32 bit virtual memory and physical memory.
//Access to the page table is only via the CR3 register.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vmemory.h"

#define OUT_TLB "../bin/tlb_out.txt"

bool FIFO_policy = true;
int **cr3;

// global parameters for translational use

int offset;
int first_addr;
int second_addr;
int pt2_ptr;
unsigned int pt1_ptr;

// used in git hit ratio

float attempts = 0;
float hits = 0;

int TLB[8][2];

int count_TLB = 0;

// TLB[x][0] is the VA
// TLB[x][1] is the PA

// The implementation of get_vpage_cr3 is provided in 
// an object file, so no need to re-implement it

void initialize_vmanager(int policy) 
{

	// open the output file for the TLB prints

	FILE* output;

    output = fopen(OUT_TLB, "w");
	
	if(output==NULL){

		fprintf(stderr, "ERROR: failed to open file...");

	}

	fclose(output);

	// Set LFU policy when passed as a parameter

	if (policy)
		FIFO_policy = false;

	// Set base pointer to page table

	cr3 = get_vpage_cr3();

	// initialize the TLB with -1 contents

	int j;

	for(j = 0; j<8; j++){

		TLB[j][0] = -1;
		TLB[j][1] = -1;

	}

}

int translate_virtual_address(unsigned int v_addr)
{

	int offset;

	// use of bitmasks and bitshifts to manipulate the original v_addr input

	// structured as 10 bits 1st pointer, 10 bits 2nd pointer, 12 bits of offset

	offset = v_addr & 0b00000000000000000000111111111111;
	pt2_ptr = v_addr & 0b00000000001111111111000000000000;
	pt2_ptr = pt2_ptr >> 12;
	pt1_ptr = v_addr & 0b11111111110000000000000000000000;
	pt1_ptr = pt1_ptr >> 22;

	unsigned int result = 0;

	// check if second page table is NULL

	if(cr3[pt1_ptr] != NULL){

		result = cr3[pt1_ptr][pt2_ptr];

		// check if physical frame has contents

		// else return -1

		if(result != -1){

			return result;

		}

	}

	return -1;
	
}

void print_physical_address(int frame, int offset)
{

	unsigned int temp;

	int countFRAME = 0;
	int countOFF = 0;

	temp = frame;

	// count the hex characters of frame

	while(temp>0){

		temp = temp / 16;
		countFRAME++;

	}

	temp = offset;

	// count hex characters of offset

	while(temp>0){

		temp = temp / 16;
		countOFF++;

	}

	// concatenation of 0x + frame + offset

	// includes appending of 0's given frame or offset is underfilled

	printf("0x");

	int i;

	if(frame==-1){

		frame = 0xfffff;

	}

	for (i = 0; i < 5-countFRAME; i++)
	{
		printf("0");
	}

	printf("%x", frame);

	for (i = 0; i < 3-countOFF; i++)
	{
		printf("0");
	}

	printf("%x\n", offset);

	return;

}

int get_tlb_entry(int n)
{
	
	attempts++;
	
	int i = 0;

	// iterate through TLB looking for matching 20 MSB of virtual address

	for(i=0; i<8; i++){

		if(TLB[i][0]==n){
			
			// if found, iterate hits, return frame of said 20 MSB of virtual address

			hits++;
			
			return TLB[i][1];

		}

	}

	return -1;

}

void populate_tlb(int v_addr, int p_addr) 
{

	int counter;

	// when TLB is full begin FIFO policy

	if(count_TLB==8){ // given TLB is full;

		for(counter=7; counter>0; counter--){

			TLB[counter][0] = TLB[counter-1][0];
			TLB[counter][1] = TLB[counter-1][1];

		}

		TLB[0][0] = v_addr;
		TLB[0][1] = p_addr;

	} else { // work to fill the TLB with expected FIFO policy behavior

		TLB[7-count_TLB][0] = v_addr;
		TLB[7-count_TLB][1] = p_addr;

		count_TLB++;

	}

	return;

}

float get_hit_ratio()
{
	
	// the ratio of hits to total get calls

	return hits/attempts;

}

// Write to the file denoted by OUT_TLB
void print_tlb()
{

	FILE* output;

	// output file to append TLB prints

    output = fopen(OUT_TLB, "a");

	if(output==NULL){

		fprintf(stderr, "ERROR: failed to open file...");

	}

	int i;

	// prints the 20 MSB VA and PA frame with preceeding "0x"

	for(i = 0; i<8; i++){

		fprintf(output, "0x%x 0x%x\n", TLB[i][0], TLB[i][1]);

	}

	// per requested new line

	fprintf(output, "\n");

    fclose(output);

	return;

}
