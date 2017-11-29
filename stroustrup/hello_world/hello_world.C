#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** arg) {

//	cout<< "Hellow World!\n";
	printf("This is the Hello world program\nThis program will also make use of sizeof fnction\n");
	printf("integer = %li\nchar = %li\npointers\n\t to integer = %ld\n\t to char =%ld\n", sizeof(int), sizeof(char), sizeof(int*), sizeof(char*));
	printf("\n Now for some ASCII code\n");
	char i;
	printf("Char INT Hexa\n");
	for(i=97;i<=122;i++)
		printf("%c = %d   %x\n", i, i, i);
	
	printf("Char INT Hexa\n");
	for(i=48;i<=58;i++)
		printf("%c = %d   %x \n", i, i, i);

    char s[] = "String";
    printf("String size= %lu \n", sizeof(s)-1);
}
