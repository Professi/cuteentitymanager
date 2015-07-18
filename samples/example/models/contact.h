#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include "entity.h"

class Contact: public CuteEntityManager::Entity {
    Q_OBJECT

    Q_PROPERTY(QString content READ getContent WRITE setContent)
    Q_PROPERTY(Category category READ getCategory WRITE setCategory)
    Q_PROPERTY(QString label READ getLabel WRITE setLabel)

  public:
    enum Category {EMAIL, MOBILE, LANDLINE, MESSENGER, EXTRA} ;
    Q_ENUM(Category)
    Q_INVOKABLE Contact() {}
    Contact(QString label, Category category, QString content);

    QString getContent() const;
    void setContent(const QString &value);

    QString getLabel() const;
    void setLabel(const QString &value);

    Category getCategory() const;
    void setCategory(const Category &value);

protected:
    QString content;
    Category category;
    QString label;
};

#endif // CONTACT_H
