#pragma once

#include <QPixmap>

#include "opencv2/opencv.hpp"

namespace freemapper {

  using Shape = std::vector<cv::Point>;

  class Scene
  {
  public:
    // Create black image
    Scene();

    // Create image from an OpenCV matrix representation
    Scene( cv::Mat matrix );

    void gray();

    // Apply Gauss blurry filter
    void gauss();

    // Apply Canny's edge detection
    void canny();

    // Combine two images, algorithm has to be selected
    //Image combine( Image image );

    // Draw a shape on top of this images
    void drawShape( const Shape &shape );

    // Return Qt pixmap to render image in QML
    QImage qImage();

    // OpenCV matrix representation of this imageh
    cv::Mat matrix() { return _matrix; }


    /*
    auto gauss() -> Image;
    auto canny() -> Image;

    auto matrix() -> Mat;

    auto drawShape() -> void;
    */


  private:
    cv::Mat _matrix = cv::Mat{};
  };
}

