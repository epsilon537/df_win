#ifndef __DF_BOX_H__
#define __DF_BOX_H__

#include "Vector.h"
namespace df {

	class Box {
	private:
		Vector m_corner; //Upper left corner of box.
		float m_horizontal; //Horizontal dimension.
		float m_vertical; //Vertical dimension.

	public:
		//Create box with (0,0) for all params.
		Box();

		//Create box with given params
		Box(Vector init_corner, float init_horizontal, float init_vertical);

		//Set upper left corner of box.
		void setCorner(Vector new_corner);

		//Get upper left corner of box.
		Vector getCorner() const;

		//Set horizontal size of box.
		void setHorizontal(float new_horizontal);

		//Get horizontal size of box.
		float getHorizontal() const;


		//Set vertical size of box.
		void setVertical(float new_vertical);

		//Get vertical size of box.
		float getVertical() const;

		//Compare to boxes for equality
		bool operator==(const Box& other);

		//Compare to boxes for inequality2
		bool operator!=(const Box& other);
	};
}

#endif /*DF_BOX_H*/
