#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsView>

#include "qextserialport.h"

#define MATRIX_PANEL_X         3
#define MATRIX_PANEL_Y         2
#define MATRIX_PANEL_LEDS_X    8
#define MATRIX_PANEL_LEDS_Y    8
#define MATRIX_PANEL_LEDS      (MATRIX_PANEL_LEDS_X*MATRIX_PANEL_LEDS_Y)
#define MATRIX_LEDS_X          (MATRIX_PANEL_X*MATRIX_PANEL_LEDS_X)
#define MATRIX_LEDS_Y          (MATRIX_PANEL_Y*MATRIX_PANEL_LEDS_Y)
#define MATRIX_LEDS            (MATRIX_LEDS_X*MATRIX_LEDS_Y)

class LedMatrix : public QObject
{
     Q_OBJECT
public:
    explicit LedMatrix(QObject *parent = 0);
    ~LedMatrix();

    bool openPortByName(QString portName);
    void closePort();
    QString portName();

    bool isConnected();

    void show();
    void showScene(QGraphicsScene * scene);
    void showView(QGraphicsView * view);
    QImage* frame();


private:
    QextSerialPort *_port;
    QImage *_frame;
    unsigned char _framebuffer[MATRIX_LEDS*3];
    bool _connected;
signals:
    void updated();
    void connected(bool connected = true);
public slots:
    
};

#endif // LEDMATRIX_H
