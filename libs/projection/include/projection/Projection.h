#pragma once

#include <thread>

#include <QObject>
#include <QDebug>

#include <model/Scene.h>

namespace freemapper {

class Projection : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
  Q_PROPERTY(Scene::Ptr scene READ scene WRITE setScene NOTIFY sceneChanged)

signals:
  void enabledChanged();
  void sceneChanged();

public:
  Q_INVOKABLE void on();
  Q_INVOKABLE void off();

  bool enabled() const { return m_enabled; }
  void setEnabled( const bool & );

  Scene::Ptr scene() const { return m_scene; }
  void setScene( const Scene::Ptr & );

private:
  bool m_enabled = false;

  Scene::Ptr m_scene;
  std::unique_ptr<std::thread> m_thread = nullptr;
};

}
