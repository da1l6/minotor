#include "minafallingobjects.h"

#include <QDebug>

MinaFallingObjects::MinaFallingObjects(QObject *object) :
    MinoAnimation(object),
    _alive(false)
{
    _ecrPosition.setStartValue(0.0);
    _ecrPosition.setEndValue(1.0);

    //First line of properties
    _beatDuration = new MinoItemizedProperty(this);
    _beatDuration->setObjectName("duration");
    _beatDuration->setLabel("Duration");
    _beatDuration->addItem("1/4", 6);
    _beatDuration->addItem("1/2", 12);
    _beatDuration->addItem("1", 24);
    _beatDuration->addItem("2", 48);
    _beatDuration->addItem("4", 96);
    _beatDuration->addItem("8", 192);
    _beatDuration->addItem("16", 384);
    _beatDuration->setCurrentItem("1");
    _beatDuration->setLinear();

    _generatorDensity = new MinoPropertyReal(this);
    _generatorDensity->setObjectName("density");
    _generatorDensity->setLabel("Density");

    _generatorDirection = new MinoItemizedProperty(this);
    _generatorDirection->setObjectName("direction");
    _generatorDirection->setLabel("Direction");
    _generatorDirection->addItem("Right", 0);
    _generatorDirection->addItem("Left", 1);
    _generatorDirection->addItem("Up", 2);
    _generatorDirection->addItem("Down", 3);
    _generatorDirection->addItem("Rand.", 4);
    _generatorDirection->setCurrentItem("Down");

    _generatorLength = new MinoItemizedProperty(this);
    _generatorLength->setObjectName("length");
    _generatorLength->setLabel("Length");
    _generatorLength->addItem("1", 1);
    _generatorLength->addItem("2", 2);
    _generatorLength->addItem("3", 3);
    _generatorLength->addItem("4", 4);
    _generatorLength->addItem("5", 5);
    _generatorLength->addItem("6", 6);
    _generatorLength->addItem("7", 7);
    _generatorLength->addItem("8", 8);
    _generatorLength->addItem("9", 9);
    _generatorLength->addItem("10", 10);
    _generatorLength->addItem("11", 11);
    _generatorLength->addItem("12", 12);
    _generatorLength->setLinear();
    _generatorLength->setCurrentItem("8");

    _generatorCurve = new MinoPropertyEasingCurve(this, true);
    _generatorCurve->setObjectName("curve");
    _generatorCurve->setLabel("Curve");
}

void MinaFallingObjects::animate(const unsigned int uppqn, const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn)
{
    (void)qn;
    (void)ppqn;

    QColor color = _color->color();
    _ecrPosition.setEasingCurve(_generatorCurve->easingCurveType());

    unsigned int direction = _generatorDirection->currentItem()->real();
    const unsigned int length = _generatorLength->currentItem()->real();
    const unsigned int duration = _beatDuration->currentItem()->real();
    QGraphicsItem *item = NULL;
    if (_enabled && _beatFactor->isBeat(gppqn))
    {
        int randomPos;
        unsigned int density = 0;
        if(direction == 4)
        {
            direction = qrand() % 4;
        }
        switch (direction)
        {
        case 0: // Left
        case 1: // Right
            density = 1 + (_generatorDensity->value() * (_boundingRect.height()-1));
            break;
        case 2: // Bottom
        case 3: // Top
            density = 1 + (_generatorDensity->value() * (_boundingRect.width()-1));
            break;
        }

        for (unsigned int i=0;i<density;i++)
        {
            const qreal progress = (qreal)i/(qreal)density;
            const qreal step = 1.0/(qreal)density;
            switch(direction)
            {
            case 0:
            {
                //left to right
                QLinearGradient grad(0.0, 0.0, length, 0.0);
                grad.setColorAt(0.0, Qt::transparent);
                grad.setColorAt(1, color);
                randomPos = (qreal)((progress + (qrandF()*step))*_boundingRect.height());
                item = _scene->addLine(0, randomPos, length, randomPos, QPen(QBrush(grad),1));
            }
                break;
            case 1:
            {
                //right to left
                QLinearGradient grad(0.0, 0.0, length, 0.0) ;
                grad.setColorAt(0.0, color) ;
                grad.setColorAt(1, Qt::transparent) ;
                randomPos = (qreal)((progress + (qrandF()*step))*_boundingRect.height());
                item = _scene->addLine(0, randomPos, length, randomPos, QPen(QBrush(grad),1));
            }
                break;
            case 2:
            {
                //bottom to top
                QLinearGradient grad(0.0, 0.0, 0.0, length) ;
                grad.setColorAt(0.0, color) ;
                grad.setColorAt(1, Qt::transparent) ;
                randomPos = (qreal)((progress + (qrandF()*step))*_boundingRect.width());
                item = _scene->addLine(randomPos, 0, randomPos, length, QPen(QBrush(grad),1));
            }
                break;
            case 3:
            {
                //top to bottom
                QLinearGradient grad(0.0, 0.0, 0.0, length) ;
                grad.setColorAt(0.0, Qt::transparent) ;
                grad.setColorAt(1, color) ;
                randomPos = (qreal)((progress + (qrandF()*step))*_boundingRect.width());
                item = _scene->addLine(randomPos, 0, randomPos, length, QPen(QBrush(grad),1));
            }
                break;
            }

            item->setData(MinaFallingObjects::Direction, direction);
            MinoAnimatedItem maItem (uppqn, duration, item);
            _itemGroup.addToGroup(item);
            _animatedItems.append(maItem);
        }

    }
    for (int i=_animatedItems.count()-1;i>-1;i--)
    {
        const MinoAnimatedItem item = _animatedItems.at(i);
        if (uppqn > (item._startUppqn+item._duration))
        {
            delete item._graphicsItem;
            _animatedItems.removeAt(i);
        }
        else
        {
            const qreal progress = item.progressForUppqn(uppqn);
            const int itemDirection = item.graphicsItem()->data(MinaFallingObjects::Direction).toInt();
            switch(itemDirection)
            {
            case 0:
            {
                //left to right
                _animatedItems.at(i)._graphicsItem->setPos((_ecrPosition.valueForProgress(progress)*((qreal)_boundingRect.width()+(length*2))-length),item._graphicsItem->pos().y());
            }
                break;
            case 1:
            {
                //right to left
                _animatedItems.at(i)._graphicsItem->setPos(((1-_ecrPosition.valueForProgress(progress))*((qreal)_boundingRect.width()+(length*2))-length),item._graphicsItem->pos().y());
                break;
            }
            case 2:
            {
                //bottom to top
                _animatedItems.at(i)._graphicsItem->setPos(item._graphicsItem->pos().x(),((1-_ecrPosition.valueForProgress(progress))*((qreal)_boundingRect.height()+(length*2))-length));
                break;
            }
            case 3:
            {
                //top to bottom
                _animatedItems.at(i)._graphicsItem->setPos(item._graphicsItem->pos().x(),((_ecrPosition.valueForProgress(progress))*((qreal)_boundingRect.height()+(length*2))-length));
                break;
            }
            }
        }
    }

    if(!_enabled && !_animatedItems.count())
    {
        MinoAnimation::setAlive(false);
        _alive = false;
    }
}

void MinaFallingObjects::setAlive(const bool on)
{
    if(on)
    {
        MinoAnimation::setAlive(true);
        _alive = on;
    }
    else
    {
        // Nothing to do: we let animate() detected that if animation is alive...
    }
}