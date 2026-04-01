#ifndef CABLE_VIEWER_H
#define CABLE_VIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include "cable.h"  // ваш класс Cable

namespace util {

class CableViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CableViewer(QWidget *parent = nullptr);
    void setCable(const domain::Cable& cable);

private:
    void drawCable();

    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    domain::Cable currentCable;

    // Параметры отрисовки
    static constexpr int CONTACT_RADIUS = 4;
    static constexpr int VERTICAL_SPACING = 40;
    static constexpr int HORIZONTAL_OFFSET = 100;
};

} // namespace util

#endif // CABLE_VIEWER_H
