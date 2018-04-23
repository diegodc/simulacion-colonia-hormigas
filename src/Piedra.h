#ifndef __PIEDRA_H__
#define __PIEDRA_H__

#include "Elemento.h"

class Piedra : public Elemento {

	public:

		Piedra() {
		}

		virtual ~Piedra() {
		}

		virtual bool SosHoja() const {
			return false;
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
			return true;
		}

		virtual bool SosSemilla() const {
			return false;
		}

		virtual char getSalida() const {
			return SALIDA_PIEDRA;
		}

};

#endif /*__PIEDRA_H__*/
