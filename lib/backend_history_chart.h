#ifndef BACKEND_HISTORY_CHART_H
#define BACKEND_HISTORY_CHART_H

#include <QObject>
#include<QVariant>
class Backend_history_chart : public QObject
{
    Q_OBJECT
    //������Ա������
    Q_PROPERTY(QVariantList operNames READ operNames )
    Q_PROPERTY(QString operName  WRITE setOperName NOTIFY operNameChanged)
    //ʵ��������
    Q_PROPERTY(QVariantList experimentNames READ experimentNames)



public:
    explicit Backend_history_chart(QObject *parent = nullptr);


    //ʵ����Ա�������б�
    QVariantList operNames();
    //��ǰʵ����Ա������
    void setOperName(const QString &operName);

    //TODO:����ʵ�����ֵ�����
    QVariantList experimentNames(); //Ҫͨ��ѡ��Ĳ���Ա���ֱ䶯
    //TODO:����Ҫ��ʾ��ģ����������

    //TODO:ͨ��ʵ����Ա����--��ʵ�����ֺ�Ҫ��ʾģ����--��ʵ������--����ȡ������ֵ���Ŵ�|��βʱ��

    //TODO:������ֵ
    //TODO:��βʱ��
signals:
    void operNameChanged();
private:
    QString operName;
    QVariantList list_experimentNames;
};

#endif // BACKEND_HISTORY_CHART_H
