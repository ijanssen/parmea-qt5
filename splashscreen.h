#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

namespace Lines {

class SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen(const QPixmap &pixmap = QPixmap());
    virtual ~SplashScreen();

    void lockPortraitOrientation();
    void releaseOrientation();

protected:
  virtual void mousePressEvent(QMouseEvent *event);

private:
    int m_orientation;
};

}

#endif // SPLASHSCREEN_H
