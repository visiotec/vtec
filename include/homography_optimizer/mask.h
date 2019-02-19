#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_MASK
#define VTEC_HOMOGRAPHY_OPTIMIZER_MASK

#include <homography_optimizer/aux.h>

namespace VTEC
{
class ImageMask
{
private:
  size_t size_;

  size_t valid_;

  float sampling_rate_;

public:
  bool* mask;

  size_t size() const;

  size_t valid() const;

  bool full() const;

  float samplingRate() const;

  ImageMask();

  ImageMask(size_t size, float sampling_rate = 1.0);

  ImageMask(const ImageMask& old);

  ~ImageMask();

  void reset(float sampling_rate = 1.0);

  cv::Mat sample(cv::Mat in);

  void maskFromThreshold(cv::Mat in, double threshold);

  ImageMask getRobustMask(cv::Mat in);

  int checkZero(const cv::Mat pattern);

  cv::Mat toMat();

  void fromWeights(cv::Mat weights);
};
}  // namespace VTEC

#endif /* VTEC_HOMOGRAPHY_OPTIMIZER_MASK */