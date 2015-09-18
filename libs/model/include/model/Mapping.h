#pragma once

#include <thread>

namespace freemapper {

class Mapping
{
public:
  using MappingPtr = std::shared_ptr< Mapping >;

  int shapes;
};

} // namespace freemapper

