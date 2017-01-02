#include "occasion.h"

Occasion::Occasion() : Entity()
{
    m_text.clear();
}

Occasion::Occasion(QString text)
{
    m_text=text;
}
QString Occasion::text()
{
    return m_text;
}

void Occasion::setText(QString &text)
{
    m_text = text;
}


