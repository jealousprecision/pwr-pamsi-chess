#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
public:
    QSFMLCanvas(
        QWidget* parent,
        const QPoint& pos,
        const QSize& size,
        unsigned frameTime = 0);  // interval in ms

protected:
    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;

    QPaintEngine* paintEngine() const override;
    void showEvent(QShowEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    QTimer timer_;
    bool initialized_ = false;
};
