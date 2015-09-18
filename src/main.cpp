#include <iostream>
#include <string>
#include <utility>

#include <QObject>
#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QDebug>

#include <gui/CaptureImage.h>
#include <capture/CameraCapture.h>
#include <projection/Projection.h>

int main (int argc, char *argv[])
{
  using namespace freemapper;

  QApplication app(argc, argv);

  // QML initialization: start engine and load qml file
  QQmlApplicationEngine qmlEngine;

  qmlRegisterType< Projection >   ("freemapper.Projection",     1, 0, "Projection");
  qmlRegisterType< CameraCapture >("freemapper.CameraCapture",  1, 0, "CameraCapture");
  qmlRegisterType< CaptureImage > ("freemapper.CaptureImage",   1, 0, "CaptureImage");

    // Scene image / video
  qmlEngine.load( QUrl( QStringLiteral("../qml/main.qml") ) );

  // Query qml component for later use
  // auto qml = qmlEngine.rootObjects().first();

  //QObject::connect( &app, &QApplication::aboutToQuit, &audioEngine, &AudioEngine::stop );

  // Execute and wait until exit signal received from UI
  return app.exec();
}

