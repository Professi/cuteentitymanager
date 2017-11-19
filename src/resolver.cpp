#include "resolver.h"
#include <QSqlRecord>
using namespace CuteEntityManager;

Resolver::Resolver(QSharedPointer<Database> db)
{
    this->db = db;
}

QList<QHash<QString, QVariant>> Resolver::convertQueryResult(QSqlQuery &q) {
    QList<QHash <QString, QVariant>> listmap = QList<QHash <QString, QVariant>>();
    this->db->select(q);
    QSqlRecord rec = q.record();
    QStringList l = QStringList();
    qint16 field_count = rec.count();
    for (int var = 0; var < field_count; ++var) {
        l.append(rec.fieldName(var));
    }
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    while (q.next()) {
        for (int var = 0; var < field_count; ++var) {
            map.insert(l.at(var), q.value(rec.indexOf(l.at(var))));
        }
        listmap.append(map);
    }
    return listmap;
}
