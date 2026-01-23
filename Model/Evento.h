#ifndef EVENTO_H
#define EVENTO_H
#include <QString>
#include <QDate>
class EventVisitor;
class Evento{
private:
    QString nome;
    QString tag;
    QString desc;
    QDate data;
public:
    Evento(QString,QString,QString,QDate);
    QString getNome() const;
    QString getTag() const;
    QString getDesc() const;
    QDate getData() const;
    void setNome(const QString&);
    void setTag(const QString&);
    void setDesc(const QString&);
    void setData(const QDate&);
    virtual void acceptVisitor(EventVisitor&) = 0;
    virtual ~Evento() = default;
    virtual QJsonObject toJson() const;
    virtual bool operator==(const Evento&) const;
};
Q_DECLARE_METATYPE(Evento*)
#endif // EVENTO_H
