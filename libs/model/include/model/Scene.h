#pragma once

#include <thread>

#include <QPixmap>

#include "opencv2/opencv.hpp"

#include <model/Mapping.h>

namespace freemapper {

class Scene : public QObject
{
  Q_OBJECT

public:
  using Ptr = std::shared_ptr< Scene >;

  Scene();

  // Create image from an OpenCV matrix representation
  void          setMatrix( const cv::Mat &matrix );

  Mapping::Ptr  mapping() const { return _mapping; }

  // ...
  void    gray();

  // Apply Gauss blurry filter
  void    gauss();

  // Apply Canny's edge detection
  void    canny();

  // Return Qt pixmap to render image in QML
  QImage  qImage();

  // OpenCV matrix representation of this imageh
  cv::Mat matrix() { return _matrix; }

  void    createMapping();
private:
  cv::Mat       _matrix   = cv::Mat{};
  Mapping::Ptr  _mapping;
};

} // namespace freemapper

