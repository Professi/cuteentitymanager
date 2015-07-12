#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include "entity.h"
#include "enums.h"

class Contact: public CuteEntityManager::Entity
{
    Q_OBJECT

    Q_PROPERTY(QString content READ content WRITE setContent)
    Q_PROPERTY(ContactCategory category READ category WRITE setCategory)
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    Q_INVOKABLE Contact() {}
    Contact(QString label, ContactCategory category, QString content);
    // getters
    QString content() {return m_content;}
    ContactCategory category() {return m_category;}
    QString label() {return m_label;}


    // setters
    void setContent(QString content) {m_content=content;}
    void setCategory(ContactCategory category) {m_category=category;}
    void setLabel(QString label) {m_label=label;}

protected:
    // members
    QString m_content;
    ContactCategory m_category;
    QString m_label;
};

#endif // CONTACT_H
