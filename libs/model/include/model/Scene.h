#pragma once

#include <thread>

#include <QPixmap>

#include "opencv2/opencv.hpp"

namespace freemapper {

  class Scene
  {
  public:
    //
    using Ptr = std::shared_ptr< Scene >;

    // Create black image
    Scene();

    // Create image from an OpenCV matrix representation
    Scene( cv::Mat matrix );

    // Capture image from connected cam
    // void capture();

    // ...
    void gray();

    // Apply Gauss blurry filter
    void gauss();

    // Apply Canny's edge detection
    void canny();

    // Combine two images, algorithm has to be selected
    //Image combine( Image image );

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

