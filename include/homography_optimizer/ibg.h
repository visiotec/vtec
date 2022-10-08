#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#include <homography_optimizer/AbstractHomographyOptimizer.h>
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
class IBGHomographyOptimizer : public AbstractHomographyOptimizer
{
public:
  
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

  
  /************************
  **** Debug Functions ****
  ************************/

  /**
   * @brief      Sets the use of tukey weights instead of talwar
   */
  void setUseTukeyWeights();
  
  /****************************
  **** END Debug Functions ****
  *****************************/


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
