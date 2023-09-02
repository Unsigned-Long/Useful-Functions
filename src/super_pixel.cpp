#include <utility>
#include "opencv2/opencv.hpp"
#include "opencv2/ximgproc/slic.hpp"
#include "artwork/logger/logger.h"

class MySuperPixelHandler {
    using Ptr = std::shared_ptr<MySuperPixelHandler>;
protected:
    cv::Mat _imgSrc;
    cv::Mat _imgWithMask;
    cv::Mat _imgMask;
    cv::Mat _imgMaskInv;
    cv::Mat _imgDst;

public:
    explicit MySuperPixelHandler(cv::Mat imgSrc) : _imgSrc(std::move(imgSrc)) {}

    static Ptr Create(const cv::Mat &imgSrc) {
        return std::make_shared<MySuperPixelHandler>(imgSrc);
    }

    bool Process(int size) {
        cv::Mat labImg;
        cv::cvtColor(_imgSrc, labImg, cv::COLOR_BGR2Lab);
        auto slic = cv::ximgproc::createSuperpixelSLIC(labImg, cv::ximgproc::SLICType::SLICO, size, 10);
        slic->iterate(20);

        int numSuperpixels = slic->getNumberOfSuperpixels();
        LOG_VAR(numSuperpixels)

        slic->getLabelContourMask(_imgMask, false);

        cv::bitwise_not(_imgMask, _imgMaskInv);
        cv::bitwise_and(_imgSrc, _imgSrc, _imgWithMask, _imgMaskInv);

        cv::Mat outLabels;
        slic->getLabels(outLabels);
        _imgDst = labImg.clone();

        for (int i = 0; i < numSuperpixels; ++i) {
            cv::Vec<double, 3> sum;
            int count = 0;
            for (int r = 0; r < _imgSrc.rows; ++r) {
                for (int c = 0; c < _imgSrc.cols; ++c) {
                    if (outLabels.at<int>(r, c) == i) {
                        sum += _imgDst.at<cv::Vec3b>(r, c);
                        ++count;
                    }
                }
            }
            auto avg = sum / count;
            for (int r = 0; r < _imgSrc.rows; ++r) {
                for (int c = 0; c < _imgSrc.cols; ++c) {
                    if (outLabels.at<int>(r, c) == i) {
                        _imgDst.at<cv::Vec3b>(r, c) = avg;
                    }
                }
            }
        }

        cv::cvtColor(_imgDst, _imgDst, cv::COLOR_Lab2BGR);

        return true;
    }

    [[nodiscard]] const cv::Mat &GetImgDst() const {
        return _imgDst;
    }

    [[nodiscard]] const cv::Mat &GetImgMask() const {
        return _imgMask;
    }

    [[nodiscard]] const cv::Mat &GetImgMaskInv() const {
        return _imgMaskInv;
    }

    [[nodiscard]] const cv::Mat &GetImgWithMask() const {
        return _imgWithMask;
    }
};

int main() {
    std::string filename = "Z30_3626-已增强-降噪.jpg";
    auto img = cv::imread("/home/csl/Documents/super_pixel/src/" + filename);
    auto handler = MySuperPixelHandler::Create(img);
    handler->Process((img.cols + img.rows) / 120.0);
    cv::imwrite("/home/csl/Documents/super_pixel/dst/" + filename, handler->GetImgDst());

    return 0;
}