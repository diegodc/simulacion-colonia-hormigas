#ifndef __ELEMENTOS_H__
#define __ELEMENTOS_H__

class Elemento {

	public:

		Elemento(){
		}

		virtual ~Elemento() {
		}

		virtual bool SosHoja() const = 0;

		virtual bool SosHormiga() const = 0;

		virtual bool SosHormiguero() const = 0;

		virtual bool SosPlanta() const = 0;

		virtual bool SosPiedra() const = 0;

		virtual bool SosSemilla() const = 0;

		virtual char getSalida() const = 0;

};

#endif /*__ELEMENTOS_H__*/
