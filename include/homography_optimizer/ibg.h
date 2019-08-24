#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#include <homography_optimizer/homography_optimizer_interface.h>
#include <vector>
#include <iostream>
#include <homography_optimizer/types.h>
#include <opencv2/highgui/highgui.hpp>

namespace VTEC
{
class IBGHomographyOptimizerImpl;

/**
 * @brief      Class for FULL homography optimizer interface. 8 degrees of freedom in the homography.
 */
class IBGHomographyOptimizer : public HomographyOptimizerInterface
{
public:
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
   * @brief      Predicts a Homography value using ZNCC correlation in a
   *             neighborhood around the current Homography value
   *
   * @param[in]  reference  The reference
   * @param      H          The tentative Homography
   *
   * @return     zncc score associated with the prediction.
   */
  double znccLocalPredict(const cv::Mat& reference, cv::Mat& H);

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

  /************************
  **** Debug Functions ****
  ************************/

protected:
  /* Pointer to implementation class */
  IBGHomographyOptimizerImpl* optimizer;

}; /* class HomographyOptimizer */

/**
 * @brief      Class for affine homography optimizer. 6 degrees of freedom in the homography.
 */
class IBGAffineHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  IBGAffineHomographyOptimizer();
  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGAffineHomographyOptimizer */

/**
 * @brief      Class for stretch homography optimizer. 4 degrees of freedom in the homography.
 */
class IBGStretchHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  IBGStretchHomographyOptimizer();

  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGStretchHomographyOptimizer */

/**
 * @brief      Class for affine homography optimizer. 6 degrees of freedom in the homography.
 */
class IBGFullHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  IBGFullHomographyOptimizer();

  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGFullHomographyOptimizer */

class IBHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  IBHomographyOptimizer();

  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double sampling_rate = 1.0);

}; /* class IBHomographyOptimizer */

}  // namespace VTEC

#endif