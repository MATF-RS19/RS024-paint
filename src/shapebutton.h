#ifndef SHAPEBUTTON_H
#define SHAPEBUTTON_H

#include <QToolButton>
#include <QDebug>

class ShapeButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ShapeButton(QWidget *parent = nullptr);
};

#endif // SHAPEBUTTON_H
