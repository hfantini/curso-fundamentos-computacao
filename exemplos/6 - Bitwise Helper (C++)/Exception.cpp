#include <iostream>

#ifndef SYSTEM_EXCEPTIONS
#define SYSTEM_EXCEPTIONS

typedef struct 
{
	const wchar_t* title;
	const wchar_t* message; // ERROR MESSAGE

} Exception;

#endif // !SYSTEM_EXCEPTIONS
