#ifndef VTEC_ABSTRACT_HOMOGRAPHY_OPTIMIZER_HEADER
#define VTEC_ABSTRACT_HOMOGRAPHY_OPTIMIZER_HEADER
#include <homography_optimizer/homography_optimizer_interface.h>
#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <memory> // shared ptr

namespace VTEC
{
class IBGHomographyOptimizerImpl;

/**
 * @brief      Abstract class, implementing the homography optimizer interface. 
 */
class AbstractHomographyOptimizer : public HomographyOptimizerInterface
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
#ifdef DEBUG_METHOD
  /**
   * @brief      Gets the homography sequence.
   *
   * @return     The homography sequence.
   */
  std::vector<cv::Mat> getHomographySequence();

  /**
   * @brief      Gets the number of iterations.
   *
   * @return     The number of iterations.
   */
  std::vector<int> getNbIterations();

  /**
   * @brief      Gets the number of features.
   *
   * @return     The number of features.
   */
  std::vector<int> getNbFeatures();

/*********************************************
************** END Debug Functions ***********
**********************************************/
#endif

protected:
  /* PIMPL PATTERN : Pointer to implementation class */
  std::shared_ptr<IBGHomographyOptimizerImpl> optimizer;

  
  
}; /* class AbstractHomographyOptimizer */

}  // namespace VTEC

#endif
