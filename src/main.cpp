#include <iostream>
#include <string>
#include <utility>

#include <QObject>
#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QDebug>

#include <gui/QVideoProvider.h>
#include <projection/Projection.h>

int main (int argc, char *argv[])
{
  //using namespace freemapper;

  QApplication app(argc, argv);

  // cv::findContours()

  // QML initialization: start engine and load qml file
  QQmlApplicationEngine qmlEngine;

  QVideoProvider *videoProvider = new QVideoProvider();
  qmlEngine.addImageProvider( QString("capture"), videoProvider);  
  qmlEngine.load( QUrl( QStringLiteral("../qml/main.qml") ) );

  // Query qml component for later use
  auto qml = qmlEngine.rootObjects().first();

  //
  Projection projection;

  //
  QQuickItem* projectionToggle = qml->findChild<QQuickItem*>( "projectionOnOff" );

  QObject::connect( projectionToggle, SIGNAL(clicked()), &projection, SLOT(onOff()));
  //QObject::connect( &app, &QApplication::aboutToQuit, &audioEngine, &AudioEngine::stop );

  // Execute and wait until exit signal received from UI
  return app.exec();
}

