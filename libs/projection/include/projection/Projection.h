#pragma once

#include <thread>

#include <QObject>
#include <QDebug>

#include <model/Scene.h>
#include <model/Mapping.h>

namespace freemapper {

class Projection : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool         enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
  Q_PROPERTY(Mapping::Ptr mapping READ mapping WRITE setMapping NOTIFY mappingChanged)

signals:
  void enabledChanged();
  void mappingChanged();

public:
  ~Projection();

  Q_INVOKABLE void on();
  Q_INVOKABLE void off();

  bool          enabled() const { return m_enabled; }
  void          setEnabled( const bool & );

  Mapping::Ptr  mapping() const { return m_mapping; }
  void          setMapping( const Mapping::Ptr & );

private:
  using ThreadPtr = std::unique_ptr<std::thread>;

  bool          m_enabled = false;
  ThreadPtr     m_thread = nullptr;
  Mapping::Ptr  m_mapping;
};

}
