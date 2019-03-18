#ifndef VTEC_HOMOGRAPHY_OPTIMIZER_AUX_H
#define VTEC_HOMOGRAPHY_OPTIMIZER_AUX_H

#include <opencv2/opencv.hpp>

#define MAD_NOISE 2.0
#define MAD_MAGIC_NUMBER 1.4826
#define TALWAR_MAGIC_NUMBER 2.795
#define TUKEY_MAGIC_NUMBER 4.6851

namespace VTEC
{
double getMedian(cv::Mat mat);

double getMadIntensity(const cv::Mat in);

cv::Mat getTalwarWeights(const cv::Mat& in);

cv::Mat getTukeyWeights(const cv::Mat& in);

void warpPoints(cv::Point2f& p, cv::Mat H);

void drawResult(cv::Mat& image, cv::Mat H, double score, int bbox_size_x, int bbox_size_y,
                cv::Scalar color = cv::Scalar(255, 255, 255));
}  // namespace VTEC

#endif /* VTEC_HOMOGRAPHY_OPTIMIZER_AUX_H */