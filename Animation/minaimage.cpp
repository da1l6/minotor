/*
 * Copyright 2012, 2013 Gauthier Legrand
 * Copyright 2012, 2013 Romuald Conty
 * 
 * This file is part of Minotor.
 * 
 * Minotor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minotor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Minotor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "minaimage.h"

#include <QGraphicsProxyWidget>
#include <QDebug>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents, true);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPointF(), _image);
}

void ImageWidget::resizeEvent(QResizeEvent *)
{
    // Dirty rescale of previously saved image
    if(!_image.isNull())
        //_image = _image.scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        _image = _image.scaled(size(),Qt::IgnoreAspectRatio);
}

void ImageWidget::setImage(QImage *image)
{
    if(image->isNull())
        _image = *image;
    else
        //_image = image->scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        _image = image->scaled(size(),Qt::IgnoreAspectRatio);
}

MinaImage::MinaImage(QObject *parent) :
    MinoAnimation(parent),
    _imageIndex(0)
{
    // Color is not usable in this animation
    delete _color;
    _color = NULL;

    _imageWidget = new ImageWidget();
    _imageWidget->resize(_boundingRect.size());

    _itemGroup.addToGroup(_scene->addWidget(_imageWidget));

    _generatorCurve = new MinoPropertyEasingCurve(this, true);
    _generatorCurve->setObjectName("curve");
    _generatorCurve->setLabel("Curve");

    _imageFilename = new MinoPropertyFilename(this);
    connect(_imageFilename, SIGNAL(filenameChanged(QString)), SLOT(loadFromFile(QString)));
    _imageFilename->setFilename("spaceinvader.gif");
}

MinaImage::~MinaImage()
{
    foreach(QImage* i, _imageList)
    {
        delete i;
    }
    _imageList.clear();
}

void MinaImage::loadFromFile(const QString& filename)
{
    QImageReader ir;
    ir.setFileName(filename);

    if(ir.canRead())
    {
        foreach(QImage* i, _imageList)
        {
            delete i;
        }
        _imageList.clear();

        while(ir.canRead())
            _imageList.append(new QImage(ir.read()));

        if(_imageList.count())
            _imageWidget->setImage(_imageList.at(0));
    }
}

void MinaImage::animate(const unsigned int uppqn, const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn)
{
    (void)uppqn;
    (void)ppqn;
    (void)qn;

    if(_imageList.count())
    {
        if(_imageList.count() != 1)
        {
            QEasingCurve ecImageIndex(_generatorCurve->easingCurveType());
            const qreal pos = ecImageIndex.valueForProgress(_beatFactor->progressForGppqn(gppqn));
            int imageIndex = (pos*0.999999999*_imageList.count());
            if(imageIndex>=_imageList.count())
                imageIndex = _imageList.count()-1;
            if(_imageIndex != imageIndex)
            {
                _imageIndex = imageIndex;
                _imageWidget->setImage(_imageList.at(_imageIndex));
            }
        }
    }
}
