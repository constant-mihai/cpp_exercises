#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define NOK 0
#define OK 1

typedef char* string;

typedef enum {
	no_value,
	Char_Argument='c',
	String_Argument='s',
	Int_Argument='d',
} argument_types_e;

int get_token (const char* string, int *token) {
	unsigned int i=0, pos[20], t=0;
	bzero(pos, 20*sizeof(int));
 
	token = (int*)malloc(3*sizeof(int));
	if (token == 0) {
		printf("Error allocation memory\n");
		goto error;
	}
	printf("second pointer addr = %p\n", token);
 
	for (i=0;i<strlen(string);i++) {
		if (string[i]=='%' && (string[i+1]=='s' || string[i+1]=='d' || string[i+1]=='c')) {
			/* Increment counter for memory allocation and save position */
			pos[t++]=string[i+1];
		} else if (string[i]=='%' && (string[i+1]!='s' || string[i+1]!='d' || string[i+1]!='c')) {
			printf("Unrecognized type\n");
			goto error;
		} else continue;
	}

	for (i=0;i<t;i++) {
		*(token+i) = pos[i];
		printf("%c\n", *(token+i));
	}
	return OK;
error:
	return NOK;
}

int get_arg(va_list *ap, int *token, int i, char *c, string *s, int *d) {

	 switch (token[i]) {
//		case First_Argument:
//			s = va_arg(ap, char*);
//			break;
		case Char_Argument:
			*c =(char) va_arg(*ap, int);
			break;
		case String_Argument: 
			*s = va_arg(*ap, char*);
			printf("%s\n", *s);
			break;
		case Int_Argument:
			*d = va_arg(*ap, int);
			break;
		default:
			printf("Error invalid type\n");
			goto error;
			break;
	}
	return OK;
error:
	return NOK;
}

void error_test(const char *error_txt ...) {

	va_list ap;
	va_start(ap, error_txt);
	char 	c=0;
	string	 s=0;
	s = new char;
	int 	d=0, i=0;
	int 	*token = 0, res = 0;
	printf("pointer addr = %p\n", token);
	if (!token) {
//		token = (int*)malloc(3*sizeof(int));
//		if (token == 0) {
//			printf("Error allocation memory\n");
//			goto error;
//		}
		if (!get_token(error_txt, token)) goto error;
		if (!token) {printf("WTF\n"); goto error;}
	}
	for (;;i++) {
		res = get_arg(&ap, token, i, &c, &s, &d);
		if (res != OK) break;
	}

	va_end(ap);
	printf("%s %c %s %d \n", error_txt, c, s, d);
	return;
error:
	printf("Error in error test\n");
	return;
}


int main(int argc, char** argv) {
	printf("Testing\n");
 	const char *string = {"This is the test string: %c %s %d \0"};
	const char *asd = {"bsd"};
	error_test(string, 'c', asd, 7);
}
