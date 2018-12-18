#include <homography_optimizer/ibg_interface.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vtec_core/draw.h>
#include <vtec_core/image.h>

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
#define PIXEL_KEEP_RATE 1.0

int main(int argc, char **argv) {
  std::string directory = ".";
  std::string file_prefix = "/seq/im";
  int digit_width = 3;

  /* Use first image in the sequence to initialize tracker*/
  VTEC::Image I;

  std::ostringstream fileNameStream;
  fileNameStream << directory << file_prefix << std::setw(digit_width)
                 << std::setfill('0') << 0 << ".pgm";

  I.loadPGM(fileNameStream.str());

  /* Tracker initialization with reference image */
  /* Choose between the three variants Full, Strectch and Affine */
  VTEC::IBGFullHomographyOptimizer myTracker;
  myTracker.initialize(MAX_NB_ITERATION_PER_LEVEL, MAX_NB_PYR_LEVEL,
                       PIXEL_KEEP_RATE);
  myTracker.setReferenceTemplate(I, BBOX_POS_X, BBOX_POS_Y, BBOX_SIZE_X,
                                 BBOX_SIZE_Y);

  /* Save the tracked pattern */
  VTEC::Image reference_template;
  myTracker.getReferenceTemplate(reference_template);
  reference_template.savePGM(directory + "/res/patr.pgm");

  /* Run the tracker and print result */
  int current_image_number = 0;
  VTEC::Image current_template;

  /* Optimization parameters */
  VTEC::Homography H;
  float alpha = 1.0;
  float beta = 0.0;
  myTracker.getHomography(H);

  /* optimization stats */
  double score;

  /* loop through the images in a sequence */
  while (current_image_number < 100) {
    /* load next image in the sequence */
    std::ostringstream fileNameStream;
    fileNameStream << directory << file_prefix << std::setw(digit_width)
                   << std::setfill('0') << current_image_number << ".pgm";
    std::cout << "processing image: " << fileNameStream.str() << std::endl;

    if (I.loadPGM(fileNameStream.str()) == false) {
      std::cout << "Unable to load next file. Exiting..." << std::endl;
      break;
    };

    /* run the optimization and record time*/
    score = myTracker.optimize(I, H, alpha, beta, VTEC::ZNCC_PREDICTOR);

    if (score == -1.0) {
      std::cout << "optimization failed" << std::endl;
      break;
    } else {
      std::cout << "Score: " << score << std::endl;
    }

    std::cout << "Homography: " << std::endl;
    printf("[%f, %f, %f\n%f, %f, %f\n%f, %f, %f]\n", H[0] / H[8], H[1] / H[8],
           H[2] / H[8], H[3] / H[8], H[4] / H[8], H[5] / H[8], H[6] / H[8],
           H[7] / H[8], H[8] / H[8]);

    myTracker.getCurrentTemplate(current_template);

    /* Draw a bounding box using the calculated homography onto the image */
    drawResult(BBOX_SIZE_X, BBOX_SIZE_Y, H, I);

    /* Save images, annotated and the current pattern warped */
    std::string annotaded_image_path, current_template_path;
    char filename_string[200];
    sprintf(filename_string, "%s/res/im%d.pgm", directory.c_str(),
            current_image_number);
    annotaded_image_path = std::string(filename_string);

    sprintf(filename_string, "%s/res/pc%d.pgm", directory.c_str(),
            current_image_number);
    current_template_path = std::string(filename_string);

    I.savePGM(annotaded_image_path);
    current_template.savePGM(current_template_path);

    current_image_number += 3;
  }

  return 0;
}