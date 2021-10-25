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
	
	//Free the page table
	free_resources();
	return 0;
}
