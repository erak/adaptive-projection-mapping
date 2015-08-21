#include <thread>

#include <QObject>
#include <QDebug>


class Projection : public QObject
{
  Q_OBJECT

public:
  void on();
  void off();

public slots:
  void onOff();

private:
  bool m_running = false;
  std::unique_ptr<std::thread> m_thread = nullptr;
};


