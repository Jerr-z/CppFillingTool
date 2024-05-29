/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
	scale();
    
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    // find position based on the scaled image
    unsigned int x = (unsigned int) p.x % scaledimg.width();
    unsigned int y = (unsigned int) p.y % scaledimg.height();
    // add brightness
    RGBAPixel temp = *scaledimg.getPixel(x,y);
    temp.r = (unsigned char) std::min((int) temp.r + (int) brightamount, 255);
    temp.g = (unsigned char) std::min((int) temp.g + (int) brightamount, 255);
    temp.b = (unsigned char) std::min((int) temp.b + (int) brightamount, 255);
    // return
    return temp;
}

/**
 * Add your private QuarterColorPicker function implementations below
 */

void QuarterColorPicker::scale() {
    scaledimg = PNG(referenceimg.width()/2, referenceimg.height()/2);
    for (unsigned int sy = 0, y=0; y < referenceimg.height(); y+=2, sy++) {
        for (unsigned int sx = 0, x=0; x < referenceimg.width(); x+=2, sx++) {
            *scaledimg.getPixel(sx,sy) = interpolate(referenceimg.getPixel(x,y), referenceimg.getPixel(x+1,y), 
                                            referenceimg.getPixel(x,y+1), referenceimg.getPixel(x+1,y+1));
        }
    }
}

RGBAPixel QuarterColorPicker::interpolate(RGBAPixel* tl, RGBAPixel* tr, RGBAPixel* bl, RGBAPixel* br) {
    // interpolate over the x axis
    double r = ((double) tl->r + (double) tr->r)/2;
    double g = ((double) tl->g + (double) tr->g)/2;
    double b = ((double) tl->b + (double) tr->b)/2;

    double r2 = ((double) bl->r + (double) br->r)/2;
    double g2 = ((double) bl->g + (double) br->g)/2;
    double b2 = ((double) bl->b + (double) br->b)/2;
    // y-axis
    double r3 = (r+r2)/2;
    double g3 = (g+g2)/2;
    double b3 = (b+b2)/2;
    
    return RGBAPixel((int)r3, (int) g3, (int) b3);
}