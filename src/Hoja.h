#ifndef __HOJA_H__
#define __HOJA_H__

#include "Definiciones.h"
#include "Elemento.h"

class Hoja : public Elemento {
	
	public:

		Hoja() {
		}

		virtual ~Hoja() {
		}

		virtual bool SosHoja() const {
			return true;
		}

		virtual bool SosHormiga() const {
			return false;
		}

		virtual bool SosHormiguero() const {
			return false;
		}

		virtual bool SosPlanta() const {
			return false;
		}

		virtual bool SosPiedra() const {
			return false;
		}

		virtual bool SosSemilla() const {
			return false;
		}

		virtual char getSalida() const {
			return SALIDA_HOJA;
		}

};

#endif /*__HOJA_H__*/
