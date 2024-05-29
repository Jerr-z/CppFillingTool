/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"
#include "queue.h"
#include <vector>
#include <set>
/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    // Complete your implementation below
	borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
    for (int i = 0; i < img.height(); i++) {
        fillable.push_back(vector<int>());
        for (int j = 0; j < img.width(); j++) {
            fillable[i].push_back(0);
        }
    }
    determineFillRegion();
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    
    if (fillable[p.y][p.x] == 1) {
        return bordercolor;
    }
    return *img.getPixel(p.x,p.y);
}



/**
 * Add your private BorderColorPicker function implementations below
 */

    
void BorderColorPicker::determineFillRegion() {
    // determine border first O(n)
    // fillable[y][x] !!!!!!!!!!!!!!!!!!!!!!!!!

    vector<pair<int,int>> positions;
    vector<pair<int,int>> borders;
    for (int y = -1; y <= (int) img.height(); y++) {
        borders.push_back(pair<int,int>({-1,y}));
        borders.push_back(pair<int,int>({img.width(),y}));
    }
    for (int x = -1; x <= (int) img.width(); x++) {
        borders.push_back(pair<int,int>({x,-1}));
        borders.push_back(pair<int,int>({x,img.height()}));
    }

    for (int y = 0; y < (int) img.height(); y++) {
        for (int x = 0; x < (int) img.width(); x++) {
            RGBAPixel* p = img.getPixel(x,y);
            //todo
            if (p->distanceTo(seedcolor) < tolerance) {
                // if p is fillable but neighbors arent, add neighbor position to borders


                if (x-1 >= 0) {
                    if (img.getPixel(x-1,y)->distanceTo(seedcolor)>tolerance) {
                        borders.push_back(pair<int,int>({x-1,y}));
                        fillable[y][x] = 1;
                    }
                }

                

                if (x+1 < img.width()) {
                    if (img.getPixel(x+1,y)->distanceTo(seedcolor)>tolerance) {
                        borders.push_back(pair<int,int>({x+1,y}));
                        fillable[y][x] = 1;
                    }

                }


                if (y-1 >= 0) {
                    if (img.getPixel(x,y-1)->distanceTo(seedcolor)>tolerance) {
                        borders.push_back(pair<int,int>({x,y-1}));
                        fillable[y][x] = 1;
                    }
                }



                if (y+1 < img.width()) {
                    if (img.getPixel(x,y+1)->distanceTo(seedcolor)>tolerance) {
                        borders.push_back(pair<int,int>({x,y+1}));
                        fillable[y][x] = 1;
                    }
                }

                // enqueue all the fillable positions
                positions.push_back(pair<int,int>({x,y}));
            }
        }
    }

    // begin terrible runtime O(mn)
    for (auto pos: positions) {

        // check through all borders and compute distance :)
        // for loop...
        // if find a distance short enough then set position as fillable, break loop
        for (auto b: borders) {
            if (pos==b) break;
            int distance2 = (pos.first - b.first)*(pos.first - b.first) + (pos.second - b.second)*(pos.second - b.second);
            if (distance2 <= borderwidth*borderwidth) {
                fillable[pos.second][pos.first] = 1;
                break;
            }
        }
    }

}