#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER

#include <homography_optimizer/mask.h>

namespace VTEC
{
enum PredictorType
{
  NO_PREDICTOR = 0,
  ZNCC_PREDICTOR = 1
};
}  // namespace VTEC

#endif /* VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER */