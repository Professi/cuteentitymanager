/*
    Small test class
    Copyright (C) 2013 Christian Ehringfeld <c.ehringfeld@t-online.de>

    This file is part of OpenTeacherTool.

    OpenTeacherTool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenTeacherTool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenTeacherTool.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "artikel.h"

//QHash<QString, QString> Artikel::getProperties(DatabaseType type) {
//    QHash<QString, QString> h = QHash<QString, QString>();
//    h.insert("id",this->idColumnSQL());
//    h.insert("preis","DOUBLE");
//    h.insert("name","TEXT");
//    return h;
//}

//PersistenceType Artikel::getPersistenceType() {
//    return OpenTeacherTool::LOCAL;
//}

//QHash<QString, Entity*> *Artikel::getRelations() {
//    return this->relations;
//}

//QHash<QString, QVariant> *Artikel::getAttributeValues() {
//    this->attributeValues->insert("id",this->id);
//    this->attributeValues->insert("name",this->name);
//    this->attributeValues->insert("preis",this->preis);
//    return this->attributeValues;
//}

//void Artikel::setAttributes(QHash<QString, QVariant> h) {
//    this->id = h.value("id").toInt();
//    this->name = h.value("name").toString();
//    this->preis = h.value("preis").toDouble();
//}



double Artikel::getPreis() const {
    return preis;
}

void Artikel::setPreis(double value) {
    preis = value;
}

QString Artikel::getName() const {
    return name;
}

void Artikel::setName(const QString &value) {
    name = value;
}

Artikel::~Artikel() {

}

Artikel::Artikel(double preis, QString name) : Entity(){
    this->preis = preis;
    this->name = name;
}


