#ifndef SIGNAL_VALS_H
#define SIGNAL_VALS_H

#include <QObject>
using namespace std;
class Signal_vals : public QObject
{
    Q_OBJECT
public:
    explicit Signal_vals(QObject *parent = nullptr);
    void add_val_to_db(float val,QString name,int id_experiment);
    vector<float> get_val_by_experimentId_from_db(int id_experiment);

signals:

};

#endif // SIGNAL_VALS_H
