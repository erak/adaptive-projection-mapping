#include <thread>

#include <QObject>
#include <QDebug>


class Projection : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

signals:
  void enabledChanged();

public:
  Q_INVOKABLE void on();
  Q_INVOKABLE void off();

  bool enabled() const { return m_enabled; }
  void setEnabled( const bool &enabled ) { m_enabled = enabled; }

private:
  bool m_enabled = false;
  std::unique_ptr<std::thread> m_thread = nullptr;
};


