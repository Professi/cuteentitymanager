/*
 * Copyright (C) 2015 Christian Ehringfeld <c.ehringfeld@t-online.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RELATION_H
#define RELATION_H
#include <QString>
namespace CuteEntityManager {
enum RelationType {
    ONE_TO_ONE, //e.g. specialization, heritage
    ONE_TO_MANY, //@OneToMany(cascade=ALL, mappedBy="customer")
    MANY_TO_ONE, //1-n  Entity foreign key in same table
    MANY_TO_MANY,
};

enum CascadeType {
    ALL,
    MERGE,
    PERSIST,
    REFRESH,
    REMOVE,
};

class Relation {
  public:
    Relation();
    Relation(QString propertyName, RelationType type, bool optional = true);
    /**
     * @brief Relation
     * @param propertyName
     * @param type
     * @param mappedBy Q_PROPERTY in foreign Entity
     */
    Relation(QString propertyName, RelationType type, QString mappedBy, QString tableName = "",
             CascadeType cascadeType = ALL);
    ~Relation();
    RelationType getType() const;
    void setType(const RelationType &value);

    QString getPropertyName() const;
    void setPropertyName(const QString &value);

    bool getOptional() const;
    void setOptional(bool value);

    QString getMappedBy() const;
    void setMappedBy(const QString &value);

    QString getTableName() const;
    void setTableName(const QString &value);

    CascadeType getCascadeType() const;
    void setCascadeType(const CascadeType &value);

  protected:
    QString propertyName;
    QString mappedBy;
    QString tableName;
    RelationType type;
    CascadeType cascadeType;
    bool optional;

};
}

#endif // RELATION_H
