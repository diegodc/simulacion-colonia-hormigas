#ifndef __SEMILLA_H__
#define __SEMILLA_H__

#include "Elemento.h"

class Semilla : public Elemento {

	public:

		Semilla() {
		}

		virtual ~Semilla() {
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
			return false;
		}

		virtual bool SosSemilla() const {
			return true;
		}

		virtual char getSalida() const {
			return SALIDA_SEMILLA;
		}

};

#endif /*__SEMILLA_H__*/
