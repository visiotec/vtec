#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_FACTORY_HEADER
#define VTEC_HOMOGRAPHY_OPTIMIZER_FACTORY_HEADER

#include <memory> // shared ptr
#include <homography_optimizer/homography_optimizer_interface.h>
#include <homography_optimizer/AbstractHomographyOptimizer.h>
#include <homography_optimizer/unified.h>
#include <homography_optimizer/ibg.h>

namespace VTEC
{
class HomographyOptimizerFactory
{
public:
    
    static std::unique_ptr<VTEC::AbstractHomographyOptimizer> create(std::string name) ;
    
}; // class
} // namespace

// about string comparison with ==
// https://stackoverflow.com/questions/9158894/differences-between-c-string-and-compare

#endif
