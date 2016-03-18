/**
 * @file rgbapixel.cpp
 * Implementation of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#include "rgbapixel.h"

RGBAPixel::RGBAPixel() : red(255.0), green(255.0), blue(255.0), alpha(255.0)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(float r, float g, float b)
	: red(r), green(g), blue(b), alpha(255.0)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(float r, float g, float b,
		             float a) : red(r), green(g), blue(b), alpha(a)
{
	/* nothing */
}

bool RGBAPixel::operator==(RGBAPixel const & other) const
{
	return red == other.red && green == other.green && blue == other.blue &&
		alpha == other.alpha;
}

bool RGBAPixel::operator!=(RGBAPixel const & other) const
{
	return !(*this == other);
}

bool RGBAPixel::operator<(RGBAPixel const & other) const
{
	if (red != other.red)
		return red < other.red;
	if (green != other.green)
		return green < other.green;
	return blue < other.blue;
}

std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel)
{
	out << "(" << (int) pixel.red << "," << (int) pixel.green << ","
		<< (int) pixel.blue << ")";
	if (pixel.alpha != 255)
		out << " a:" << pixel.alpha;
	return out;
}
