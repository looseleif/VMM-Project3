//main.c program to translate the virtual addresses from the virtual.txt
//into the physical frame address. Project 3 - CSci 4061

#include <stdio.h>
#include <stdlib.h>
#include "vmemory.h"

#define INPUT_FILE "../bin/virtual.txt"

int main(int argc, char* argv[])
{
	if (argc > 2) {
		printf("Too many arguments, enter up to one argument\n");
		exit(-1);
	}

	int policy = (argc == 2) ? 1:0;

	initialize_vmanager(policy);

	//TODO: Translate all of the virtual addresses in INPUT_FILE
	//	Print the corresponding physical addresses line by line
	//	Make sure to populate the TLB as you go!
	//	Output the TLB at the start and end along with the hit rate
	
	// test 1

	//unsigned int x = 0xaf199f2d;

	//int tran_offset1 = x & 0b00000000000000000000111111111111;

	//int translation_frame1 = translate_virtual_address(x);

	//print_physical_address(translation_frame1, tran_offset1);

	//int x_cut = (0b11111111111111111111000000000000 & x) >> 12;

	// test 2

	//unsigned int y = 0x559b5978;

	//int tran_offset2 = y & 0b00000000000000000000111111111111;

	//int translation_frame2 = translate_virtual_address(y);

	//print_physical_address(translation_frame2, tran_offset2);

	//int y_cut = (0b11111111111111111111000000000000 & y) >> 12;

	/*
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(y_cut,translation_frame2);
	populate_tlb(y_cut,translation_frame2);
	populate_tlb(y_cut,translation_frame2);
	populate_tlb(y_cut,translation_frame2);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	populate_tlb(x_cut,translation_frame1);
	*/

	/*
	printf("get tlb7: %x\n", get_tlb_entry(7));
	printf("get tlb6: %x\n", get_tlb_entry(6));
	printf("get tlb5: %x\n", get_tlb_entry(5));
	printf("get tlb4: %x\n", get_tlb_entry(4));
	printf("get tlb3: %x\n", get_tlb_entry(3));
	printf("get tlb2: %x\n", get_tlb_entry(2));
	printf("get tlb1: %x\n", get_tlb_entry(1));
	printf("get tlb0: %x\n", get_tlb_entry(-1));
	*/

	//print_tlb();

	//get_tlb_entry(x_cut);
	//get_tlb_entry(y_cut);

	//printf("%f\n", get_hit_ratio());

	// --- BEGIN PROCEDURE ---

	FILE* input;

    input = fopen(INPUT_FILE, "r");

	//char lineToRead[11];

	unsigned int addr_ptr;

	//fgets(lineToRead,3,input)!=NULL

	print_tlb();

	int count = 0;

	while(fscanf(input, " 0x%x", &addr_ptr)!=-1){
		
		//count++;
		//printf("%d\n",count);
		

		int tlb_return;

		unsigned int x = addr_ptr;

		int x_cut = (0b11111111111111111111000000000000 & x) >> 12;

		int tran_offset = x & 0b00000000000000000000111111111111;

		if((tlb_return = get_tlb_entry(x_cut))==-1){

			int translation_frame = translate_virtual_address(x);
			
			populate_tlb(x_cut,translation_frame);

			print_physical_address(translation_frame, tran_offset);
			
		} else {

			print_physical_address(tlb_return, tran_offset);

		}

	}

	print_tlb();

	printf("%f\n", get_hit_ratio());

	//Free the page table
	free_resources();
	return 0;
}
