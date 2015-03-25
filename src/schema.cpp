#include "schema.h"
using namespace CuteEntityManager;

Schema::Schema() {
    this->typeMap = QSharedPointer<QHash<QString,QString>>(new QHash<QString,QString>());
}

Schema::~Schema() {

}

QString Schema::quoteSimpleTableName(QString name) {
    //    return strpos($name, "`") !== false ? $name : "`" . $name . "`";
}

QString Schema::quoteSimpleColumnName(QString name)
{
//return strpos($name, '`') !== false || $name === '*' ? $name : '`' . $name . '`';
}

