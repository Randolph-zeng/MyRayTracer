/*
 * ViewPlane.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Ruiss
 */

#ifndef VIEWPLANE_H_
#define VIEWPLANE_H_

class ViewPlane {
public:
	int hres;//horizontal and vertical resolution
	int vres;
	float psize; //pixel size

	float gamma;	//gamma correction factor
	float inv_gamma;
	bool out_of_gamut;	//if or not the color display is out of gamut

	ViewPlane();   								// default Constructor

	ViewPlane(const ViewPlane& vp);				// copy constructor

	ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator

	~ViewPlane();   							// destructor

	void
	set_hres(const int h_res);

	void
	set_vres(const int v_res);

	void
	set_pixel_size(const float size);

	void
	set_gamma(const float g);

	void
	set_gamut_display(const bool show);
};


// ------------------------------------------------------------------------------ set_hres

inline void
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}


// ------------------------------------------------------------------------------ set_vres

inline void
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}


// ------------------------------------------------------------------------------ set_pixel_size

inline void
ViewPlane::set_pixel_size(const float size) {
	psize = size;
}


// ------------------------------------------------------------------------------ set_gamma

inline void
ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}


// ------------------------------------------------------------------------------ set_gamut_display

inline void
ViewPlane::set_gamut_display(const bool show) {
	out_of_gamut = show;
}

#endif /* VIEWPLANE_H_ */
