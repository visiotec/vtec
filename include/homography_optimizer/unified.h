#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER
#include <homography_optimizer/homography_optimizer_interface.h>
#include <opencv2/highgui/highgui.hpp>
#include <homography_optimizer/types.h>

namespace VTEC
{
class UnifiedHomographyOptimizerImpl;

class UnifiedHomographyOptimizer : public HomographyOptimizerInterface
{
public:
  UnifiedHomographyOptimizer();

  /**
   * @brief      Initialization function
   *
   * @param[in]  max_nb_iter       The maximum number of iterations per pyramid level
   * @param[in]  max_nb_pyr_level  The maximum number of pyr level
   * @param[in]  sampling_rate     The sampling rate
   */
  void initialize(const int max_nb_iter, const int max_nb_pyr_level, const double sampling_rate);

  /**
   * @brief      Gets the current warped template.
   *
   * @param      img   The warped template
   */
  void getCurrentTemplate(cv::Mat& img);

  /**
   * @brief      Gets the reference template.
   *
   * @param      img   The image
   */
  void getReferenceTemplate(cv::Mat& img);

  /**
   * @brief      Sets the reference image.
   *
   * @param[in]  ref_image  The reference image
   *
   * @return     True if the reference image was set, false otherwise
   */
  bool setReferenceTemplate(const cv::Mat& ref_image, int posx, int posy, int sizex, int sizey);

  /**
   * @brief      Optimizes H, alpha and beta. Considers that the reference image has already been set.
   *
   * @param[in]  curr_image  The curr image
   * @param      H           { parameter_description }
   * @param      alpha       The alpha
   * @param      beta        The beta
   * @param[in]  predictor   The predictor
   *
   * @return     The ZNCC score associated with the prediction. -1.0 means the optimization failed.
   */
  double optimize(const cv::Mat& curr_image, cv::Mat& H, float& alpha, float& beta,
                  PredictorType predictor = NO_PREDICTOR);

  /**
   * @brief      Gets the homography.
   *
   * @param      H     The homography matrix.
   */
  void getHomography(cv::Mat& H);

  /**
   * @brief      Sets the homography.
   *
   * @param[in]  H     The homography matrix
   */
  void setHomography(const cv::Mat& H);

  /**
   * @brief      Sets the robust flag
   *
   * @param[in]  robust_flag  The robust flag
   */
  void setRobustFlag(bool robust_flag);

  /**
   * @brief      Sets the Feature-based weight factor.
   *
   * @param[in]  fb_factor  The feature-based weight factor
   */
  void setFBFactor(double fb_factor);

  /**
   * @brief      Sets the use of tukey weights instead of talwar
   */
  // void setUseTukeyWeights();

protected:
  // PIMPL pattern
  UnifiedHomographyOptimizerImpl* optimizer;

};  // Class UnifiedHomographyOptimizer

class FBRobustHomographyOptimizer : public UnifiedHomographyOptimizer
{
public:
  FBRobustHomographyOptimizer();

  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double sampling_rate = 1.0);

}; /* class IBHomographyOptimizer */

}  // namespace VTEC

#endif /*VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER*/