#ifndef OCCASION_H
#define OCCASION_H

#include "entity.h"
#include <QObject>

using namespace CuteEntityManager;
class Occasion : public Entity
{
    Q_OBJECT
    EM_MACRO(Occasion)
    Q_PROPERTY(QString text READ text WRITE setText)
public:
    Q_INVOKABLE explicit Occasion();
    Occasion(QString text);
    QString text();
    void setText(QString &text);

protected:
    QString m_text;

};

#endif // OCCASION_H

