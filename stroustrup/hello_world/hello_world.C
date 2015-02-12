#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** arg) {

//	cout<< "Hellow World!\n";
	printf("This is the Hello world program\nThis program will also make use of sizeof fnction\n");
	printf("integer = %d\nchar = %d\npointers\n\t to integer = %d\n\t to char =%d\n", sizeof(int), sizeof(char), sizeof(int*), sizeof(char*));
	printf("\n Now for some ASCII code\n");
	char i;
	printf("Char INT Hexa\n");
	for(i=97;i<=122;i++)
		printf("%c = %d   %x\n", i, i, i);
	
	printf("Char INT Hexa\n");
	for(i=48;i<=58;i++)
		printf("%c = %d   %x \n", i, i, i);
}
