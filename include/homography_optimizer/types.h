#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER

#include <homography_optimizer/mask.h>

namespace VTEC
{
struct TrackStruct
{
  cv::Mat** images;
  ImageMask** masks;
  cv::Mat Jc, ds;
  int miter;    //!< iteration number
  int mprec;    //!< tracking precision
  float alpha;  //!< the alpha parameter
  float beta;   //!< the beta parameter
  int nb_iter;
  cv::Mat homog;  //! < the homography <
  int size_pyram;
  double last_score;  //!
  std::vector<cv::Mat> homographies;
};

enum PredictorType
{
  NO_PREDICTOR = 0,
  ZNCC_PREDICTOR = 1
};
}  // namespace VTEC

#endif /* VTEC_HOMOGRAPHY_OPTIMIZER_TYPES_HEADER */