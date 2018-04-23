#ifndef __INTTOSTRING_H__
#define __INTTOSTRING_H__

#include <sstream>
#include <string>

std::string IntToString(unsigned int numero) {
	std::stringstream stream;
	std::string cadena;
	stream << numero;
	stream >> cadena;
	return cadena;
}

#endif /*__INTTOSTRING_H__*/
