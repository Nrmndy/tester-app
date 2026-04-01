#include "cable_viewer.h"
#include <QBoxLayout>
#include <QPen>
#include <QBrush>
#include <QGraphicsTextItem>

namespace util {

CableViewer::CableViewer(QWidget *parent)
    : QWidget(parent), currentCable()
{
    // Создаём вид и сцену
    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);

    // Включаем полосы прокрутки
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Настройка вида
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setBackgroundBrush(Qt::white);

    // Макет
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(graphicsView);
    setLayout(layout);
}

void CableViewer::setCable(const domain::Cable& cable)
{
    currentCable = cable;
    drawCable();
}

void CableViewer::drawCable()
{
    scene->clear();

    if (currentCable.GetConnectionsCount() == 0) {
        scene->addText("Нет соединений для отображения")->setDefaultTextColor(Qt::black);
        return;
    }

    int yPos = 50;  // Начальная позиция по Y

    for (int i = 0; i < currentCable.GetConnectionsCount(); ++i) {
        const auto& connection = currentCable.GetConnection(i);
        int fromPin = connection.GetFrom();
        const auto& toPins = connection.GetTo();

        // Рисуем контакт FROM
        scene->addEllipse(
            -CONTACT_RADIUS, yPos - CONTACT_RADIUS,
            2 * CONTACT_RADIUS, 2 * CONTACT_RADIUS,
            QPen(Qt::black), QBrush(Qt::blue));

        auto fromPinText = scene->addText(QString::number(fromPin));
        fromPinText->setPos(-30, yPos - 12); // 12 - полтора радиуса контакта
        fromPinText->setDefaultTextColor(Qt::black);

        // Рисуем соединения TO
        for (int j = 0; j < toPins->size(); ++j) {
            int toPin = toPins->at(j);
            int targetY = yPos + j * VERTICAL_SPACING;

            // Контакт TO
            scene->addEllipse(
                HORIZONTAL_OFFSET - CONTACT_RADIUS, targetY - CONTACT_RADIUS,
                2 * CONTACT_RADIUS, 2 * CONTACT_RADIUS,
                QPen(Qt::black), QBrush(Qt::green));

            auto toPinText = scene->addText(QString::number(toPin));
            toPinText->setPos(HORIZONTAL_OFFSET + 10, targetY - 12);
            toPinText->setDefaultTextColor(Qt::black);

            // Если адресов больше одного, то рисуем цепи ветвления с точками-соединениями
            if (j > 0) {
                auto x_connection_point = HORIZONTAL_OFFSET / 2 + CONTACT_RADIUS / 2;
                auto y_connection_point = yPos + VERTICAL_SPACING * (j - 1) - CONTACT_RADIUS / 2;

                scene->addEllipse(
                    HORIZONTAL_OFFSET / 2, y_connection_point,
                    CONTACT_RADIUS, CONTACT_RADIUS,
                    QPen(Qt::red), QBrush(Qt::red));

                scene->addLine(x_connection_point, y_connection_point + CONTACT_RADIUS / 2,
                               x_connection_point, y_connection_point + CONTACT_RADIUS / 2 + VERTICAL_SPACING,
                               QPen(Qt::red, 2));

                scene->addLine(x_connection_point, y_connection_point + CONTACT_RADIUS / 2 + VERTICAL_SPACING,
                               HORIZONTAL_OFFSET, targetY,
                               QPen(Qt::red, 2));
            } else {
                // Линия соединения
                scene->addLine(0, yPos, HORIZONTAL_OFFSET, targetY, QPen(Qt::red, 2));
            }
        }

        yPos += VERTICAL_SPACING * (toPins->size() + 1);
    }

    // Автомасштабирование
    // graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

} // namespace util
