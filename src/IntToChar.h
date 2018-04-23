#ifndef __INTTOCHAR_H__
#define __INTTOCHAR_H__

#include <sstream>

char IntToChar(unsigned int numero) {
	std::stringstream stream;
	std::string cadena;
	stream << numero;
	stream >> cadena;
	return *(cadena.c_str());
}

#endif /*__INTTOCHAR_H__*/
