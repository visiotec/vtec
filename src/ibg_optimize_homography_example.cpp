#include <homography_optimizer/ibg.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/* Bounding box left-top position  (x,y) in the first image */
#define BBOX_POS_X 200
#define BBOX_POS_Y 250

/* Bounding box size (x, y) in the first image  */
#define BBOX_SIZE_X 200
#define BBOX_SIZE_Y 200

/* Maximum number of iterations per pyramid level. Lower means less computation
 * effort */
#define MAX_NB_ITERATION_PER_LEVEL 10

/* Number of levels in the pyramid, use more if you need more precision */
#define MAX_NB_PYR_LEVEL 4

/* Sampling rate, 1.0 means 100% of points are used */
#define PIXEL_KEEP_RATE 1.0

int main(int argc, char** argv)
{
  std::string directory = ".";
  std::string file_prefix = "/seq/im";
  int digit_width = 3;

  /* Tracker initialization without reference image */
  VTEC::IBGFullHomographyOptimizer ibg_optimizer;
  ibg_optimizer.initialize(MAX_NB_ITERATION_PER_LEVEL, MAX_NB_PYR_LEVEL, PIXEL_KEEP_RATE);

  /* Load reference image */

  std::ostringstream refFileNameStream;
  refFileNameStream << directory << file_prefix << std::setw(digit_width) << std::setfill('0') << 0 << ".pgm";

  cv::Mat reference_image = cv::imread(refFileNameStream.str(), CV_LOAD_IMAGE_GRAYSCALE);
  std::cout << refFileNameStream.str() << std::endl;

  ibg_optimizer.setReferenceTemplate(reference_image, BBOX_POS_X, BBOX_POS_Y, BBOX_SIZE_X, BBOX_SIZE_Y);

  /* Load current image */
  std::ostringstream currFileNameStream;
  currFileNameStream.clear();
  currFileNameStream << directory << file_prefix << std::setw(digit_width) << std::setfill('0') << 5 << ".pgm";

  std::cout << currFileNameStream.str() << std::endl;
  cv::Mat current_image = cv::imread(currFileNameStream.str(), CV_LOAD_IMAGE_GRAYSCALE);

  /* Optimization parameters */
  cv::Mat H(3, 3, CV_64F, cv::Scalar(0));
  float alpha = 1.0;
  float beta = 0.0;

  /* Initialize Homography first guess */
  H.at<double>(0, 0) = 1.0;
  H.at<double>(0, 2) = BBOX_POS_X;
  H.at<double>(1, 1) = 1.0;
  H.at<double>(1, 2) = BBOX_POS_Y;
  H.at<double>(2, 2) = 1.0;

  std::cout << "Initial Homography: " << H << std::endl;

  VTEC::drawResult(reference_image, H, 1.0, BBOX_SIZE_X, BBOX_SIZE_Y);

  /* optimization stats */
  double score;

  /* optimize function */
  score = ibg_optimizer.optimize(current_image, H, alpha, beta, VTEC::NO_PREDICTOR);

  if (score == -1.0)
  {
    std::cout << "optimization failed" << std::endl;
    return 0;
  }
  else
  {
    std::cout << "Score: " << score << std::endl;
  }

  /* Save the results */
  VTEC::drawResult(current_image, H, score, BBOX_SIZE_X, BBOX_SIZE_Y);

  std::cout << "Estimated Homography: " << H << std::endl;

  cv::Mat current_template;
  ibg_optimizer.getCurrentTemplate(current_template);

  cv::Mat reference_template;
  ibg_optimizer.getReferenceTemplate(reference_template);

  /* Save images, annotated and the current template warped */
  std::string annotaded_image_path, current_template_path, reference_template_path, reference_image_path;
  annotaded_image_path = directory + "/res/annotated_image.pgm";
  current_template_path = directory + "/res/warped_template.pgm";
  reference_template_path = directory + "/res/reference_template.pgm";
  reference_image_path = directory + "/res/reference_image.pgm";

  cv::imwrite(reference_image_path, reference_image);
  cv::imwrite(annotaded_image_path, current_image);
  cv::imwrite(current_template_path, current_template);
  cv::imwrite(reference_template_path, reference_template);

  return 0;
}