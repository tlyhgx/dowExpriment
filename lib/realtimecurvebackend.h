#ifndef REALTIMECURVEBACKEND_H
#define REALTIMECURVEBACKEND_H

#include <QObject>

class RealTimeCurveBackend : public QObject
{
    Q_OBJECT
public:
    explicit RealTimeCurveBackend(QObject *parent = nullptr);

signals:

};

#endif // REALTIMECURVEBACKEND_H
