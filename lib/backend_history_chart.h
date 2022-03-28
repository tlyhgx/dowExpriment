#ifndef BACKEND_HISTORY_CHART_H
#define BACKEND_HISTORY_CHART_H

#include <QObject>
#include<QVariant>
class Backend_history_chart : public QObject
{
    Q_OBJECT
    //������Ա������
    Q_PROPERTY(QVariantList operNames READ operNames )
    //ѡ��Ĳ�����Ա
    Q_PROPERTY(QString operName  WRITE setOperName NOTIFY operNameChanged)
    //ʵ��������
    Q_PROPERTY(QVariantList experimentNames READ experimentNames  NOTIFY experimentNamesChanged)
    //ѡ���ʵ��
    Q_PROPERTY(QString experimentName  WRITE setExperimentName )
    //ѡ���ģ������
    Q_PROPERTY(QString analogName  WRITE setAnalogName )
    //��ѯ���ص�list��ʱ����ǰ�������ں�
    Q_PROPERTY(QVariantList recieveTimeAndVal READ recieveTimeAndVal  NOTIFY recieveTimeAndValChanged)
    //��ʾ��ʱ����β
    Q_PROPERTY(QVariantList time_start_end READ time_start_end NOTIFY time_start_endChanged )
    //��ʾ��ֵ�ķ�Χ
    Q_PROPERTY(QVariantList displayValueScope READ displayValueScope  NOTIFY displayValueScopeChanged)
public:
    //ʵ��view�Ĳ�ѯȷ������
    Q_INVOKABLE  void ask_datas_from_db();
public:
    explicit Backend_history_chart(QObject *parent = nullptr);

    //����ģ������
    void setAnalogName(const QString &analogName);
    //ʵ����Ա�������б�
    QVariantList operNames();
    //��ǰʵ����Ա������
    void setOperName(const QString &operName);
    //ѡ��ʵ������
    void setExperimentName(const QString &experimentName);
    //ʵ�����ֵ�����
    QVariantList experimentNames(); //Ҫͨ��ѡ��Ĳ���Ա���ֱ䶯

    //���ݸ�view�Ĳ�ѯ���
    QVariantList recieveTimeAndVal();



    //TODO:������ֵ
    QVariantList displayValueScope();
    //TODO:��βʱ��
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
    //����һ��list��ʱ����ǰ�������ں�
    QVariantList list_Com_Time_RecordVal;
    //��βʱ����
    QVariantList group_time_start_end;
    //��ʾֵ��Χ
    QVariantList group_val_min_max;

};

#endif // BACKEND_HISTORY_CHART_H
