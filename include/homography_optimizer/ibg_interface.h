#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_IBG_INTERFACE_HEADER
#include <homography_optimizer/types.h>
#include <vector>

namespace VTEC
{
class IBGHomographyOptimizerImpl;
class Image;

/**
 * @brief      Class for FULL homography optimizer interface. 8 degrees of freedom in the homography.
 */
class IBGHomographyOptimizer
{
public:
  /**
   * @brief      Gets the current warped template.
   *
   * @param      img   The warped template
   */
  void getCurrentTemplate(VTEC::Image& img);

  /**
   * @brief      Gets the reference template.
   *
   * @param      img   The image
   */
  void getReferenceTemplate(VTEC::Image& img);

  /**
   * @brief      Sets the reference image.
   *
   * @param[in]  ref_image  The reference image
   *
   * @return     True if the reference image was set, false otherwise
   */
  bool setReferenceTemplate(const VTEC::Image& ref_image, int posx, int posy, int sizex, int sizey);

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
  double optimize(const VTEC::Image& curr_image, Homography& H, float& alpha, float& beta, int predictor = 0);

  /**
   * @brief      Predicts a Homography value using ZNCC correlation in a
   *             neighborhood around the current Homography value
   *
   * @param[in]  reference  The reference
   * @param      H          The tentative Homography
   *
   * @return     zncc score associated with the prediction.
   */
  double znccLocalPredict(const VTEC::Image& reference, Homography& H);

  /**
   * @brief      Gets the homography.
   *
   * @param      H     The homography matrix.
   */
  void getHomography(Homography& H);

  /**
   * @brief      Sets the homography.
   *
   * @param[in]  H     The homography matrix
   */
  void setHomography(const Homography& H);

  /**
   * @brief      Gets the homography sequence.
   *
   * @return     The homography sequence.
   */
  std::vector<VTEC::Homography*> getHomographySequence();

  /**
   * @brief      Gets the number of iterations.
   *
   * @return     The number of iterations.
   */
  std::vector<int> getNbIterations();

  void virtual initialize(int max_nb_iter, int max_nb_pyr_level, double pixel_keep_rate) = 0;

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
  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGAffineHomographyOptimizer */

/**
 * @brief      Class for stretch homography optimizer. 4 degrees of freedom in the homography.
 */
class IBGStretchHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGStretchHomographyOptimizer */

/**
 * @brief      Class for affine homography optimizer. 6 degrees of freedom in the homography.
 */
class IBGFullHomographyOptimizer : public IBGHomographyOptimizer
{
public:
  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double pixel_keep_rate = 1.0);

}; /* class IBGFullHomographyOptimizer */

}  // namespace VTEC

#endif