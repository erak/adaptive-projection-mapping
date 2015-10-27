#pragma once

#include <thread>
#include <mutex>

#include <QObject>
#include <QDebug>

#include <model/Scene.h>
#include <model/Mapping.h>

namespace freemapper {

class Projection : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool         enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
  Q_PROPERTY(Scene*       scene WRITE setScene NOTIFY sceneChanged)

signals:
  void enabledChanged();
  void sceneChanged();

public:
  ~Projection();

  Q_INVOKABLE void on();
  Q_INVOKABLE void off();

  bool          enabled() const { return _enabled; }
  void          setEnabled( const bool & );

  // Mapping*      mapping() const { return m_mapping.get(); }
  void          setScene( Scene* );

private:
  using ThreadPtr = std::unique_ptr<std::thread>;

  bool          _enabled = false;
  ThreadPtr     _thread = nullptr;
  Mapping::Ptr  _mapping;

  std::mutex    _mapping_mutex;
};

}
