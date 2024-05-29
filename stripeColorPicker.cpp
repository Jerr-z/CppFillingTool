/**
 * @file stripeColorPicker.cpp
 * @description Implements the StripeColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "stripeColorPicker.h"
#include <iostream>
/**
 * Constructs a new StripeColorPicker.
 *
 * @param stripe_width The width of each alternating stripe, in pixels
 * @param stripe_color1 Color of the main stripe
 * @param stripe_color2 Color of the alternate stripe
 */
StripeColorPicker::StripeColorPicker(unsigned int stripe_width, RGBAPixel stripe_color1, RGBAPixel stripe_color2)
{
    // Complete your implementation below
	stripewidth = stripe_width;
    color1 = stripe_color1;
    color2 = stripe_color2;
}

/**
 * Picks the color for pixel (x, y).
 *
 * The stripe pattern to be drawn consists of alternating stripes each of stripewidth pixels,
 * in a 45-degree forward slash orientation.
 * e.g.  / / / / / 
 *        / / / / /
 *       / / / / / 
 *        / / / / /
 *
 * For reference, coordinate (0, 0) will be the left-most pixel of a color1 stripe.
 */
RGBAPixel StripeColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    int rowStart, colStart,nRow,nCol; // rowstart and colstart indicates which color starts your row/col
    // nrow ncol indicates how many of the same color blocks starts your row/col
    if ((p.x/stripewidth)%2 == 0) {
        colStart = 1;
    } else {
        colStart = 2;
    }

    if ((p.y/stripewidth)%2 == 0) {
        rowStart = 1;
    } else {
        rowStart = 2;
    }

    nRow = stripewidth - p.y % stripewidth;
    nCol = stripewidth - p.x % stripewidth;

    int r1,r2;
    if ((((int)p.x-nRow)/stripewidth)%2 == 0 && p.x>nRow-1) {
        r1 = 3-rowStart;
    } else {
        r1 = rowStart;
    }

    if ((((int)p.y-nCol)/stripewidth)%2 == 0 && p.y>nCol-1) {
        r2 = 3-colStart;
    } else {
        r2 = colStart;
    }

    if (r1 != r2) {
        std::cout<< "you screwed up stripe color picker" << std::endl;
    }

    if (r1 == 1) {
        return color1;
    } else {
        return color2;
    }
}

/**
 * Add your private StripeColorPicker function implementations below
 */
