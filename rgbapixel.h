/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
#include <ostream>

//using std::uint8_t;

/**
 * Represents a single pixel in an image.
 */
class RGBAPixel
{
	public:
		double red; /**< Byte for the red component of the pixel. */
		double green; /**< Byte for the green component of the pixel. */
		double blue; /**< Byte for the blue component of the pixel. */
		double alpha; /**< Byte for the alpha component of the pixel. */

        /** @cond POST_MP1 */

		/**
		 * Equality operator.
		 * @param other Other pixel to check equality with.
		 */
		bool operator==(RGBAPixel const & other) const;

		/**
		 * Inequality operator.
		 * @param other Other pixel to check inequality with.
		 */
		bool operator!=(RGBAPixel const & other) const;

		/**
		 * Less than operator. Provided to give some ordering notion to
		 * RGBAPixels.
		 * @param other Other pixel to compare with.
		 */
		bool operator<(RGBAPixel const & other) const;


		/**
		 * addition operator.
		 * RGBAPixels.
		 * @param other Other pixel to add with.
		 */
		 RGBAPixel operator+(const RGBAPixel & other);

		 /**
		 * division operator.
		 * RGBAPixels.
		 * @param numbers to be divided
		 */

		 RGBAPixel operator/(const double number);

		 RGBAPixel operator*(const double number);

        /** @endcond */

		/**
		 * Constructs a default RGBAPixel. A default pixel is completely
         * opaque (non-transparent) and white. Opaque implies that the
         * alpha component of the pixel is 255. Lower values are
         * transparent.
		 */
		RGBAPixel();

		/**
         * Constructs an opaque RGBAPixel with the given red, green, blue
         * color values. The alpha component of the pixel constructed
         * should be 255.
		 * @param red Red component for the new pixel.
		 * @param green Green component for the new pixel.
		 * @param blue Blue component for the new pixel.
		 */
		RGBAPixel(double red, double green, double blue);

        /** @cond POST_MP1 */

		/**
		 * Constructs an RGBAPixel with the given red, green, blue, and
		 * alpha components.
		 * @param red Red component for the new pixel.
		 * @param green Green component for the new pixel.
		 * @param blue Blue component for the new pixel.
		 * @param alpha Alpha component for the new pixel (controls
		 *	transparency).
		 */
		RGBAPixel(double red, double green, double blue,
				  double alpha);
        
        /** @endcond */

};




inline RGBAPixel
RGBAPixel::operator+ (const RGBAPixel & other){
	return RGBAPixel(red+other.red,green+other.green,blue+other.blue);
}

inline RGBAPixel
RGBAPixel:: operator/ (const double number){

	return RGBAPixel(red/number,green/number,blue/number);
}

inline RGBAPixel
RGBAPixel:: operator* (const double number){

	return RGBAPixel(red*number,green*number,blue*number);
}


/**
 * Stream operator that allows pixels to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param pixel Pixel to write to the stream.
 */
std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel);

/** @endcond */

#endif // RGBAPIXEL_H
