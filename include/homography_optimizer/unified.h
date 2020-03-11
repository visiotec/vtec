#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER
#include <homography_optimizer/AbstractHomographyOptimizer.h>
#include <opencv2/highgui/highgui.hpp>
#include <homography_optimizer/types.h>

namespace VTEC
{
class UnifiedHomographyOptimizerImpl;

class UnifiedHomographyOptimizer : public AbstractHomographyOptimizer
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
   * @brief      Sets the Feature-based weight factor.
   *
   * @param[in]  fb_factor  The feature-based weight factor
   */
  void setFBFactor(double fb_factor);

  /**
   * @brief      DISABLED, NO EFFECT ON THIS CLASS Sets the Feature-based weight factor.
   *
   * @param[in]  fb_factor  The feature-based weight factor
   */
  void setRobustFlag(bool robust_flag);

  
  /**
   * @brief      Sets the use of tukey weights instead of talwar
   */
  // void setUseTukeyWeights();

protected:
    /* PIMPL PATTERN : EXTRA Pointer to implementation class */
    std::shared_ptr<UnifiedHomographyOptimizerImpl> optimizer_typecast;
  
};  // Class UnifiedHomographyOptimizer

class FBRobustHomographyOptimizer : public UnifiedHomographyOptimizer
{
public:
  FBRobustHomographyOptimizer();

  void initialize(int max_nb_iter = 5, int max_nb_pyr_level = 2, double sampling_rate = 1.0);

}; /* class IBHomographyOptimizer */

}  // namespace VTEC

#endif /*VTEC_HOMOGRAPHY_OPTIMIZER_UNIFIED_HEADER*/
