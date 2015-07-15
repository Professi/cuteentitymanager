#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include "entity.h"
#include "enums.h"

class Contact: public CuteEntityManager::Entity
{
    Q_OBJECT

    Q_PROPERTY(QString content READ getContent WRITE setContent)
    Q_PROPERTY(Enums::ContactCategory category READ getCategory WRITE setCategory)
    Q_PROPERTY(QString label READ getLabel WRITE setLabel)

public:
    Q_INVOKABLE Contact() {}
    Contact(QString label, Enums::ContactCategory category, QString content);

    QString getContent() const;
    void setContent(const QString &value);

    Enums::ContactCategory getCategory() const;
    void setCategory(const Enums::ContactCategory &value);

    QString getLabel() const;
    void setLabel(const QString &value);

protected:
    QString content;
    Enums::ContactCategory category;
    QString label;
};

#endif // CONTACT_H
