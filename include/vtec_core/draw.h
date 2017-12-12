#ifndef VTEC_CORE_DRAW_HEADER
#define VTEC_CORE_DRAW_HEADER

#include <math.h>
#include <vtec_core/image.h>

/**
 * @brief      Draws a line in an image
 *
 * @param      image  The image
 * @param[in]  r1     The 1st point coordinate
 * @param[in]  c1     The 1st point coordinate
 * @param[in]  r2     The 2nd point coordinate
 * @param[in]  c2     The 2nd point coordinate
 */
void drawLine(VTEC::Image& image, int r1, int c1, int r2, int c2);

/**
 * @brief      Draws a warped bounding box on an image.
 *
 * @param[in]  sx    length in x of the bounding box
 * @param[in]  sy    length in y of the bounding box
 * @param[in]  H     Homography matrix
 * @param      I     the image
 */
void drawResult(int sx, int sy, const float H[9], VTEC::Image& I);

#endif /* VTEC_CORE_DRAW_HEADER */