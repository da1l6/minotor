#ifndef MINAVIBRATION_H
#define MINAVIBRATION_H

#include "minoanimation.h"

#include "minopropertyreal.h"
#include "easingcurvedreal.h"
#include "minopropertyeasingcurve.h"

class MinaVibration : public MinoAnimation
{
    Q_OBJECT
public:
    explicit MinaVibration(QObject *object);

    void animate(const unsigned int uppqn, const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn);

    static const MinoAnimationDescription getDescription() {
        return MinoAnimationDescription("Vibration", "Beat-synced vibration", QPixmap(":/images/vibration.png"), MinaVibration::staticMetaObject.className());
    }
    const MinoAnimationDescription description() const { return getDescription(); }
    
    void setSegments(qreal value) { _segments->setValue(value); }
    QGraphicsItem* graphicItem() { return &_itemGroup; }

signals:

public slots:

private:
    QGraphicsItemGroup _itemGroup;
    EasingCurvedReal _ecrBarLenght;
    MinoPropertyEasingCurve *_generatorCurve;

protected:
    MinoPropertyReal *_segments;

};


#endif // MINAVIBRATION_H