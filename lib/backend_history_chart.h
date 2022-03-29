#ifndef BACKEND_HISTORY_CHART_H
#define BACKEND_HISTORY_CHART_H

#include <QObject>
#include<QVariant>
class Backend_history_chart : public QObject
{
    Q_OBJECT
    //操作人员姓名组
    Q_PROPERTY(QVariantList operNames READ operNames )
    //选择的操作人员
    Q_PROPERTY(QString operName  WRITE setOperName NOTIFY operNameChanged)
    //实验名称组
    Q_PROPERTY(QVariantList experimentNames READ experimentNames  NOTIFY experimentNamesChanged)
    //选择的实验
    Q_PROPERTY(QString experimentName  WRITE setExperimentName )
    //选择的模拟量项
    Q_PROPERTY(QString analogName  WRITE setAnalogName )
    //查询返回的list，时间在前，数据在后
    Q_PROPERTY(QVariantList recieveTimeAndVal READ recieveTimeAndVal  NOTIFY recieveTimeAndValChanged)
    //显示的时间首尾
    Q_PROPERTY(QVariantList time_start_end READ time_start_end NOTIFY time_start_endChanged )
    //显示的值的范围
    Q_PROPERTY(QVariantList displayValueScope READ displayValueScope  NOTIFY displayValueScopeChanged)
public:
    //实现view的查询确定功能
    Q_INVOKABLE  void ask_datas_from_db();
public:
    explicit Backend_history_chart(QObject *parent = nullptr);

    //设置模拟量项
    void setAnalogName(const QString &analogName);
    //实验人员的名称列表
    QVariantList operNames();
    //当前实验人员的名字
    void setOperName(const QString &operName);
    //选择实验名字
    void setExperimentName(const QString &experimentName);
    //实验名字的数组
    QVariantList experimentNames(); //要通过选择的操作员名字变动

    //传递给view的查询结果
    QVariantList recieveTimeAndVal();



    //TODO:数据最值
    QVariantList displayValueScope();
    //TODO:首尾时间
    QVariantList time_start_end();
signals:
    void operNameChanged();
    void experimentNamesChanged();
    void recieveTimeAndValChanged();
    void time_start_endChanged();
    void displayValueScopeChanged();
private:
    QString operName;
    QString experimentName;
    QString analogName;
    QVariantList list_experimentNames;
    //这是一个list，时间在前，数据在后
    QVariantList list_Com_Time_RecordVal;
    //首尾时间组
    QVariantList group_time_start_end;
    //显示值范围
    QVariantList group_val_min_max;

};

#endif // BACKEND_HISTORY_CHART_H
