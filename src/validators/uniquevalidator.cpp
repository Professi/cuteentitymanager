#include "uniquevalidator.h"
#include "entitymanager.h"
using namespace CuteEntityManager;
UniqueValidator::UniqueValidator() : Validator() {
}

QList<ErrorMsg> UniqueValidator::validate(QVariant value,
        QList<Param> params) const {
    QList<ErrorMsg> msgs = QList<ErrorMsg>();
    if (!params.isEmpty()) {
        QString targetAttribute = "";
        QString targetClass = "";
        QString entityManagerID = "";
        for (int i = 0; i < params.size(); ++i) {
            if (params.at(i).getName() == "targetAttribute") {
                targetAttribute = params.at(i).getValue().toString();
            } else if (params.at(i).getName() == "entityManagerID") {
                entityManagerID = params.at(i).getValue().toString();
            } else if (params.at(i).getName() == "targetClass") {
                targetClass = params.at(i).getValue().toString();
            }
        }
        EntityManager *em = nullptr;
        if (entityManagerID.isEmpty()) {
            em = EntityManager::getDefaultInstance();
        } else {
            em = EntityManager::getInstance(entityManagerID);
        }
        if (!em) {
            msgs.append(ErrorMsg("", "No entitymanager."));
        } else {
            Query q = Query();
            auto e = EntityInstanceFactory::createInstance(
                         targetClass.toLatin1().constData());
            q.appendFrom(e->getTablename());
            delete e;
            e = nullptr;
            QHash<QString, QVariant> params = QHash<QString, QVariant>();
            params.insert(targetAttribute, value);
            q.appendWhere(em->getQueryBuilder()->where(params));
            if (em->count(q) > 0) {
                msgs.append(ErrorMsg("",
                                     "<property> \"" + value.toString() + "\" has already been taken."));
            }
        }
    } else {
        msgs.append(ErrorMsg("", "UniqueValidator has not enough parameters."));
    }
    return msgs;
}

ErrorMsg UniqueValidator::validateParam(QVariant value, Param param) const {
    Q_UNUSED(value)
    Q_UNUSED(param)
    return ErrorMsg();
}
