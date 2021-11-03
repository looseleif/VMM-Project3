//main.c program to translate the virtual addresses from the virtual.txt
//into the physical frame address. Project 3 - CSci 4061

#include <stdio.h>
#include <stdlib.h>
#include "vmemory.h"

#define INPUT_FILE "../bin/virtual.txt"

int main(int argc, char* argv[])
{

	// check argument count for errors, pertains to extra credit LFU

	if (argc > 2) {
		printf("Too many arguments, enter up to one argument\n");
		exit(-1);
	}

	int policy = (argc == 2) ? 1:0;

	// initialize page table and TLB for further use

	initialize_vmanager(policy);

	// open file for reading virtual addresses
	
	FILE* input;

    input = fopen(INPUT_FILE, "r");

	unsigned int addr_ptr;

	// print empty initialized TLB

	print_tlb();

	int count = 0;

	// scan through file of 32 bit virtual addresses

	while(fscanf(input, " 0x%x", &addr_ptr)!=-1){
		
		int tlb_return;

		unsigned int x = addr_ptr;

		// 20 MSB of virtual address

		int x_cut = (0b11111111111111111111000000000000 & x) >> 12;

		// 12 bit offset of virtual address

		int tran_offset = x & 0b00000000000000000000111111111111;

		// check if given virtual address pages are inside the TLB

		if((tlb_return = get_tlb_entry(x_cut))==-1){ // if frame was not found in TLB

			int translation_frame = translate_virtual_address(x);
			
			// add given pointers to the TLB

			populate_tlb(x_cut,translation_frame);

			// output physical address to system from translated frame

			print_physical_address(translation_frame, tran_offset);
			
		} else { // if frame was found in TLB

			// output physical address to system from TLB contents

			print_physical_address(tlb_return, tran_offset);

		}

	}

	// print TLB after full translation of input file

	print_tlb();

	// will print the division of successful TLB lookups and attempted TLB lookups

	printf("%f\n", get_hit_ratio());

	//Free the page table

	free_resources();
	
	return 0;

}
