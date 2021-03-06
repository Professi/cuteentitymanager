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
#include <QHash>
namespace CuteEntityManager {
enum class RelationType {
    ONE_TO_ONE = 0, //e.g. specialization, heritage
    ONE_TO_MANY = 1, //@OneToMany(cascade=ALL, mappedBy="customer") e.g. QList<QSharedPointer<Person>>
    MANY_TO_ONE = 2, //e.g. QSharedPointer<Person>
    //1-n  Entity foreign key in same table
    MANY_TO_MANY = 3 //e.g. QList<QSharedPointer<Person>> - realized with seperated database table
};

enum class InheritanceStrategy {
    PER_CLASS_TABLE,
    JOINED_TABLE
};

enum class CascadeType {
    ALL,
    MERGE,
    PERSIST,
    REFRESH,
    REMOVE
};

class Relation {
  public:
    explicit Relation();
    explicit Relation(QString propertyName, bool optional, RelationType type);
    /**
     * @brief Relation
     * @param propertyName
     * @param type
     * @param mappedBy Q_PROPERTY in foreign Entity
     */
    explicit Relation(QString propertyName, RelationType type,
                      QString mappedBy = QString(),
                      QList<CascadeType> cascadeType = QList<CascadeType> {CascadeType::MERGE, CascadeType::PERSIST, CascadeType::REFRESH});
    ~Relation();
    RelationType getType() const;
    QString getTypeAsString() const;
    void setType(const RelationType &value);

    QString getPropertyName() const;
    void setPropertyName(const QString &value);

    bool getOptional() const;
    void setOptional(bool value);

    QString getMappedBy() const;
    void setMappedBy(const QString &value);

    QList<CascadeType> getCascadeType() const;
    void setCascadeType(const QList<CascadeType> &value);

  protected:
    QString propertyName;
    QString mappedBy;
    RelationType type;
    QList<CascadeType> cascadeType;
    bool optional;

};

inline bool operator==(const Relation &e1, const Relation &e2) {
    return e1.getPropertyName() == e2.getPropertyName();
}

inline uint qHash(const Relation &key, uint seed) {
    return qHash(key.getPropertyName(), seed);
}

}

#endif // RELATION_H
