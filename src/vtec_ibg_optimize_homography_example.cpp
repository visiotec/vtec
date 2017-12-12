#include <vtec_core/image.h>
#include <vtec_core/draw.h>
#include <homography_optimizer/ibg_interface.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

/* Bounding box left-top position  (x,y) in the first image */
#define BBOX_POS_X                    200
#define BBOX_POS_Y                    250

/* Bounding box size (x, y) in the first image  */
#define BBOX_SIZE_X                   200
#define BBOX_SIZE_Y                   200

/* Maximum number of iterations per pyramid level. Lower means less computation effort */
#define MAX_NB_ITERATION_PER_LEVEL    5

/* Number of levels in the pyramid, use more if you need more precision */
#define MAX_NB_PYR_LEVEL              2

/* Sampling rate, 1.0 means 100% of points are used */
#define PIXEL_KEEP_RATE               1.0


int main(int argc, char** argv){
   std::string directory = ".";
   std::string file_prefix="/seq/im";
   int digit_width = 3;

   /* Tracker initialization without reference image */
   VTEC::IBGFullHomographyOptimizer ibg_optimizer;
   ibg_optimizer.initialize(MAX_NB_ITERATION_PER_LEVEL, MAX_NB_PYR_LEVEL, PIXEL_KEEP_RATE);

   /* Load reference image */
   VTEC::Image reference_image; 

   std::ostringstream refFileNameStream;  
   refFileNameStream << directory << file_prefix <<  std::setw(digit_width) << std::setfill('0') << 0 << ".pgm";

   reference_image.loadPGM(refFileNameStream.str());

   ibg_optimizer.setReferenceTemplate(reference_image, BBOX_POS_X, BBOX_POS_Y, BBOX_SIZE_X, BBOX_SIZE_Y);

   /* Load current image */
   VTEC::Image current_image; 

   std::ostringstream currFileNameStream;  
   currFileNameStream.clear();
   currFileNameStream << directory << file_prefix <<  std::setw(digit_width) << std::setfill('0') << 2 << ".pgm";

   current_image.loadPGM(currFileNameStream.str());

   /* Optimization parameters */
   VTEC::Homography H;
   float alpha = 1.0;
   float beta = 0.0;

   /* Initialize Homography first guess */
   H[0]=1.0;H[1]=0.0; H[2]=BBOX_POS_X;
   H[3]=0.0;H[4]=1.0; H[5]=BBOX_POS_Y;
   H[6]=0.0;H[7]=0.0; H[8]=1.0;

   /* optimization stats */
   double score;

   /* optimize function */
   score = ibg_optimizer.optimize(current_image, H, alpha, beta, VTEC::NO_PREDICTOR);

   if(score == -1.0){
      std::cout << "optimization failed" << std::endl;
      return 0;
   }else{
      std::cout << "Score: " << score << std::endl;
   }

   /* Save the results */
   drawResult (BBOX_SIZE_X, BBOX_SIZE_Y, H, current_image); 

   VTEC::Image current_template;
   ibg_optimizer.getCurrentTemplate(current_template);

   VTEC::Image reference_template;
   ibg_optimizer.getReferenceTemplate(reference_template);

   /* Save images, annotated and the current template warped */
   std::string annotaded_image_path, current_template_path, reference_template_path;
   annotaded_image_path = directory + "/res/annotated_image.pgm";
   current_template_path = directory + "/res/warped_template.pgm";
   reference_template_path = directory + "/res/reference_template.pgm";

   current_image.savePGM(annotaded_image_path);
   current_template.savePGM(current_template_path);
   reference_template.savePGM(reference_template_path);

   return 0;
}