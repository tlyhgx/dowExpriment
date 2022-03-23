#ifndef BACKEND_HISTORY_CHART_H
#define BACKEND_HISTORY_CHART_H

#include <QObject>
#include<QVariant>
class Backend_history_chart : public QObject
{
    Q_OBJECT
    //操作人员姓名组
    Q_PROPERTY(QVariantList operNames READ operNames )
    Q_PROPERTY(QString operName  WRITE setOperName NOTIFY operNameChanged)
    //实验名称组
    Q_PROPERTY(QVariantList experimentNames READ experimentNames)



public:
    explicit Backend_history_chart(QObject *parent = nullptr);


    //实验人员的名称列表
    QVariantList operNames();
    //当前实验人员的名字
    void setOperName(const QString &operName);

    //TODO:增加实验名字的数组
    QVariantList experimentNames(); //要通过选择的操作员名字变动
    //TODO:增加要显示的模拟量的数组

    //TODO:通过实验人员名称--》实验名字和要显示模拟量--》实验数据--》获取数据最值并放大|首尾时间

    //TODO:数据最值
    //TODO:首尾时间
signals:
    void operNameChanged();
private:
    QString operName;
    QVariantList list_experimentNames;
};

#endif // BACKEND_HISTORY_CHART_H
