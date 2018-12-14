#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER

namespace VTEC
{
/* Homography type definition */
typedef float Homography[9];

/* Predictior type list */
enum predictor_type
{
  NO_PREDICTOR = 0,
  ZNCC_PREDICTOR = 1
};
}  // namespace VTEC
#endif /* VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER */