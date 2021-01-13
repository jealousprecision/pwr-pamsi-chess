#include "widgets/QSFMLWidget.hpp"

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(
    QWidget* parent,
    const QPoint& pos,
    const QSize& size,
    unsigned frameTime) :
        QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    move(pos);
    resize(size);

    timer_.setInterval(frameTime);
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!initialized_)
    {
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
        OnInit();

        connect(&timer_, SIGNAL(timeout()), this, SLOT(repaint()));
        timer_.start();

        initialized_ = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return nullptr;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    OnUpdate();
    display();
}
