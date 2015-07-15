#include "contact.h"

Contact::Contact(QString label, Enums::ContactCategory category, QString content) {
    this->label = label;
    this->category = category;
    this->content = content;
}
QString Contact::getContent() const {
    return content;
}

void Contact::setContent(const QString &value) {
    content = value;
}
Enums::ContactCategory Contact::getCategory() const {
    return category;
}

void Contact::setCategory(const Enums::ContactCategory &value) {
    category = value;
}
QString Contact::getLabel() const {
    return label;
}

void Contact::setLabel(const QString &value) {
    label = value;
}




