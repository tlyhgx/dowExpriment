#ifndef SIGNAL_VALS_H
#define SIGNAL_VALS_H

#include <QObject>

class Signal_vals : public QObject
{
    Q_OBJECT
public:
    explicit Signal_vals(QObject *parent = nullptr);
    void add_val_to_db(float val);
    float get_val_from_db(int id_signal_val);

signals:

};

#endif // SIGNAL_VALS_H
