#ifndef EVENTO_H
#define EVENTO_H
#include <QString>
#include <QDate>
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
 //   void acceptVisitor(EventVisitor);
    virtual ~Evento() = default;
    virtual bool operator==(const Evento&) const ;
};
#endif // EVENTO_H
