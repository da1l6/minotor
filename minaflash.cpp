#include "minaflash.h"

#include <QColor>
#include <QDebug>

MinaFlash::MinaFlash(MinoProgram *program):
    MinoAnimation(program)
{
    _beatAnimatedProperty.setStartValue(QVariant(1.0));
    _beatAnimatedProperty.setEndValue(QVariant(0.0));
    _beatAnimatedProperty.setEasingCurve(QEasingCurve::OutBounce);

    _color.setObjectName("Color");
    _properties.append(&_color);

    QColor color;
    color.setHsvF(_color.value(), 1.0, 1.0);
    _rectItem = _scene->addRect(_boundingRect, QPen(Qt::NoPen),QBrush(color));
}

MinaFlash::~MinaFlash()
{
    delete _rectItem;
}

void MinaFlash::animate(const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn)
{
    (void)ppqn;
    (void)qn;
    computeAnimaBeatProperty(gppqn);

    QColor color;
    color.setHsvF(_color.value(), 1.0, 1.0);
    _rectItem->setBrush(QBrush(color));

    _rectItem->setOpacity(_beatAnimatedProperty.currentValue().toFloat());
}