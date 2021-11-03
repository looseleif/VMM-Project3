/*test machine: CSELAB_machine_name
* date: 11/02/2021
* name: Michael Johnson, Chase Anderson, Emir Sahbegovic
* x500: Joh18255, And08479, Sahbe001
*/


Purpose of the Program:

	The purpose of this program is to showcase the power/usefulness of the 
	translation lookup buffer (TLB). To accomplish this, we are using a virtual emulation of the 
	TLB, which would usually be implemented in the physical hardware of the system.

How to Compile the Program:

	Once one has correctly navigated to the source file, run the command "make" in a linux system,
	this will utilize gcc to compile and generate an output file.


What Our Program Does:

	Our program will read virtual addressess from a text file and will automatically translate 
	all of them into physical addresses. The program will then print these physical addresses
	and continuously update the TLB as it progresses through the text file. At the end of the output,
	the program will also print its hit ratio of the TLB. The contents of the TLB will be appended 
	to tlb_out.txt both before and after translation. However, each call to the vmanager will reset 
	the contents of tlb_out.txt.


External Assumptions:

	None.

Our Team:

	Michael Johnson - Joh18255
	Chase Anderson - And08479
	Emir Sahbegovic - Sahbe001

Our Contributions: 
	
	Michael - Translating addresses
	Chase - Implementation of TLB
	Emir - Main Program and Commenting