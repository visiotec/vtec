#ifndef VTEC_CORE_IMAGE_HEADER
#define VTEC_CORE_IMAGE_HEADER

#include <stdlib.h>
#include <cstdio>
#include <string>

typedef struct imageStruct imageStruct;

namespace VTEC
{
typedef struct Range
{
  size_t start;
  size_t end;
} Range;

/**
 * @brief      Class for handling single-channel images .
 */
class Image
{
private:
  /**
   * @brief      Saves a pgm header.
   *
   * @param      fp    file pointer
   * @param[in]  rows  number of rows in the image
   * @param[in]  cols  number of cols in the image
   *
   * @return     0 if successful, 1 otherwise
   */
  int savePgmHeader(FILE* fp, int rows, int cols) const;

  /**
   * @brief      Saves pgm values.
   *
   * @param      fp    file pointer
   * @param[in]  area  The area of the image
   * @param      ptr   The pointer to the image data
   *
   * @return     0 if successful, 1 otherwise
   */
  int savePgmValues(FILE* fp, int area, unsigned char* ptr) const;

  /**
   * @brief      Reads a pgm header.
   *
   * @param      fp     file pointer
   * @param      rowsp  number of image rows
   * @param      colsp  number of image cols
   *
   * @return     0 if successful, 1 otherwise
   */
  int readPgmHeader(FILE* fp, int* rowsp, int* colsp);

  /**
   * @brief      Reads pgm values.
   *
   * @param      fp    file pointer
   * @param[in]  area  The image are
   * @param      ptr   pointer to the image data
   *
   * @return     0 if successful, 1 otherwise
   */
  int readPgmValues(FILE* fp, int area, float* ptr);

  /**
   * @brief      Saves a pgm.
   *
   * @param[in]  filename  The file path
   * @param      image     The image struct
   *
   * @return     0 if successful, 1 otherwise
   */
  int savePgm(const char* filename, imageStruct* image) const;

public:
  /* struct contains the actual image data */
  imageStruct* I;

  /**
   * @brief      Empty Constructor
   */
  Image();

  /**
   * @brief      Destroys the object.
   */
  ~Image();

  /**
   * @brief      Constructor. Allocates space for the image
   *
   * @param[in]  nb_cols  The number of cols
   * @param[in]  nb_rows  The number of rows
   */
  Image(int nb_cols, int nb_rows);

  /**
   * @brief      Allocates space for the image
   *
   * @param[in]  nb_cols  The number of cols
   * @param[in]  nb_rows  The number of rows
   */
  void resize(int nb_cols, int nb_rows);

  /**
   * @brief      Saves the image to a pgm file
   *
   * @param[in]  filename  The filename
   *
   * @return     true if successful, false otherwise
   */
  bool savePGM(const std::string filename) const;

  /**
   * @brief      Loads data from a pgm file
   *
   * @param[in]  filename  The filename
   *
   * @return     true if successful, false otherwise
   */
  bool loadPGM(const std::string filename);

  /**
   * @brief      obtains the size (area) of the image
   *
   * @return     the size of the image
   */
  const size_t size() const;

  /**
   * @brief      Gets the number of points in the image that haven't been
   *             eliminated by a mask
   *
   * @return     The valid size.
   */
  const size_t getValidSize() const;

  /**
   * @brief      Obtains the image gradients in the u and v directions
   *
   * @param      du    An image containing the gradient in the u direction
   * @param      dv    An image containing the gradient in the v direction
   *
   * @return     true if successfull, false otherwise
   */
  bool grad(Image& du, Image& dv) const;

  /**
   * @brief      Multiplies the image pixels by alpha and adds beta, filtered
   *             by a mask image
   *
   * @param[in]  alpha  The alpha
   * @param[in]  beta   The beta
   * @param[in]  mask   The mask
   *
   * @return     true if successfull, false otherwise
   */
  bool applyPhotometricParametersWithMask(float alpha, float beta, const Image& mask);

  /**
   * @brief      returns the pixel value at the x and y coordinates
   *
   * @param[in]  x     x coordinate of the point in the image
   * @param[in]  y     y coordinate of the point in the image
   *
   * @return     the pixel value
   */
  float at(int x, int y) const;

  /**
   * @brief      Compares with another image
   *
   * @param      other  The other image
   *
   * @return     true if the images are equal, false otherwise
   */
  bool isEqual(Image& other) const;

  /**
   * @brief      allocates space and fills the image with a value
   *
   * @param[in]  value    The value
   * @param[in]  nb_cols  The number of cols
   * @param[in]  nb_rows  The number of rows
   */
  void fill(float value, int nb_cols, int nb_rows);

}; /* class Image */

} /* namespace VTEC */

#endif /* VTEC_CORE_IMAGE_HEADER */
