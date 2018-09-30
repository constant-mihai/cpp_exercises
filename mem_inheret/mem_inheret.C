/***************************************** 

* File Name : mem_inheret.C

* Creation Date : 06-06-2016

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

******************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <new>
#include <string.h>

class GenericClass {
	public:
		
		void* resize(size_t initialSize, size_t finalSize, void* ptr);
		unsigned long getMemSize();
		
		void* operator new(size_t size);
		void  operator delete(void* ptr);
		
		/* Placement new */
		void* operator new(size_t size, void* ptr);
		
		/* Array alloc/dealloc */
		void* operator new[](size_t size);
		void  operator delete[](void* ptr);

		/* Placement array new */
		void* operator new[](size_t size, void* ptr);

};



/* Needs to know what it is resized from */
void* GenericClass::resize(size_t initialSize, size_t finalSize, void* ptr)
{
	std::bad_alloc ba;
	void *bptr = ptr;
	ptr = realloc(ptr, finalSize);
	if (ptr == 0) {
		if (bptr != 0)
			free(bptr);
		//LOG(0, "Out of memory\n");
		throw ba;
	} else {
		//LOG(L_MEM, "Resized %p to  %ld bytes\n", ptr, finalSize-initialSize);
#if HARDCODED_DEBUG_MODE
		//lock
		//unlock
#endif
	}
	return ptr;
}

/* Ovewritten memory allocators for when running in debug mode */
void* GenericClass::operator new(size_t size)
{
    std::cout << "alloced" << std::endl;
	std::bad_alloc ba;
	void *ptr = malloc(size);
	if (ptr == 0) {
		//LOG(L_ERR, "Out of memory\n");
		throw ba;
	} else {
		//lock
		//unlock
	}
	return ptr;
}

void GenericClass::operator delete(void* ptr)
{
	if (!ptr) {
		//LOG(L_ERR, "Memory already freed\n");
		return;
	}

    std::cout << "DELETED" << std::endl;

	free(ptr);
}

void* GenericClass::operator new(size_t size, void* ptr)
{
	return ptr;
}

void* GenericClass::operator new[](size_t size)
{
	std::bad_alloc ba;
	void *ptr = malloc(size);
	if (ptr == 0) {
		//LOG(L_ERR, "Out of memory\n");
		throw ba;
	} else {
		//lock
		//unlock
	}
	return ptr;
}

void GenericClass::operator delete[](void *ptr)
{
	if (!ptr) {
		//LOG(L_ERR, "Memory already free\n");
		return;
	}

	free(ptr);
}

void* GenericClass::operator new[](size_t size, void* ptr)
{
	return ptr;
}


class SpecificClass : public GenericClass
{
    int i;
    public:
    ~SpecificClass(){ std::cout << "DEST Spec" << std::endl; };
    SpecificClass(){ std::cout << "Const Spec" << std::endl; };
};

int main (int argc, char** argv)
{
    SpecificClass *sc = new SpecificClass(); 
    delete sc;


    const char* cc = "This is a test";

    char *c = new char(20);
    memcpy(c, cc, 7);

   std::cout << c << std::endl;


    return 0;
}
