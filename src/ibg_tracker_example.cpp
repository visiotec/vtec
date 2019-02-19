#include <homography_optimizer/ibg.h>
#include <homography_optimizer/aux.h>
#include <opencv2/highgui/highgui.hpp>
#include <iomanip>

/* Bounding box left-top position  (x,y) in the first image */
#define BBOX_POS_X 250
#define BBOX_POS_Y 200

/* Bounding box size (x, y) in the first image  */
#define BBOX_SIZE_X 200
#define BBOX_SIZE_Y 200

/* Maximum number of iterations per pyramid level. Lower means less computation
 * effort */
#define MAX_NB_ITERATION_PER_LEVEL 5

/* Number of levels in the pyramid, use more if you need more precision */
#define MAX_NB_PYR_LEVEL 2

/* Sampling rate, 1.0 means 100% of points are used */
#define SAMPLING_RATE 1.0

int main(int argc, char** argv)
{
  std::string directory = ".";
  std::string file_prefix = "/seq/im";
  int digit_width = 3;

  int skip_image;

  std::ostringstream fileNameStream;
  fileNameStream << directory << file_prefix << std::setw(digit_width) << std::setfill('0') << 0 << ".pgm";

  cv::Mat reference_image = cv::imread(fileNameStream.str(), CV_LOAD_IMAGE_GRAYSCALE);

  VTEC::IBGFullHomographyOptimizer optimizer;
  optimizer.initialize(MAX_NB_ITERATION_PER_LEVEL, MAX_NB_PYR_LEVEL, SAMPLING_RATE);
  optimizer.setReferenceTemplate(reference_image, BBOX_POS_X, BBOX_POS_Y, BBOX_SIZE_X, BBOX_SIZE_Y);

  cv::Mat ref_template;
  optimizer.getReferenceTemplate(ref_template);
  cv::imwrite("./res/ref_template.pgm", ref_template);

  cv::Mat H, cur_template;

  optimizer.getHomography(H);

  cv::Mat H_original = H;

  int i;
  float alpha = 1.0;
  float beta = 0.0;

  for (i = 0; i < 10; ++i)
  {
    std::ostringstream fileNameStream;
    fileNameStream << directory << file_prefix << std::setw(digit_width) << std::setfill('0') << i << ".pgm";

    std::cout << fileNameStream.str() << std::endl;

    cv::Mat current_image = cv::imread(fileNameStream.str(), CV_LOAD_IMAGE_GRAYSCALE);

    if (current_image.empty())
    {
      std::cout << "End of image stream" << std::endl;
      break;
    }

    double score = optimizer.optimize(current_image, H, alpha, beta, VTEC::NO_PREDICTOR);
    std::cout << "RESULT" << std::endl;
    std::cout << "Score: " << score << std::endl;

    optimizer.getHomography(H);
    std::cout << "Homography: " << H << std::endl;

    VTEC::drawResult(current_image, H, score, BBOX_SIZE_X, BBOX_SIZE_Y);
    cv::imwrite(directory + "/res/annotated_image_" + std::to_string(i) + ".pgm", current_image);

    optimizer.getCurrentTemplate(cur_template);
    cv::imwrite(directory + "/res/cur_template_" + std::to_string(i) + ".pgm", cur_template);
  }
}