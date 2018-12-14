#ifndef VTEC_CORE_TYPES_HEADER
#define VTEC_CORE_TYPES_HEADER

typedef struct imageStruct
{
  int cols;     //! < width  / cols
  int rows;     //! < height / rows
  int valid;    //! < number of valid points in the image
  float* data;  //! < data
} imageStruct;

#endif /* VTEC_CORE_TYPES_HEADER*/
