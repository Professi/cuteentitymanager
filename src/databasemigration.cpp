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
#include "databasemigration.h"
using namespace CuteEntityManager;

DatabaseMigration::DatabaseMigration() : Entity() {

}

DatabaseMigration::DatabaseMigration(QString version, QDateTime applyTime) : Entity() {
    this->version = version;
    this->applyTime = applyTime;
}

DatabaseMigration::~DatabaseMigration() {

}

QString DatabaseMigration::getVersion() const {
    return version;
}

void DatabaseMigration::setVersion(const QString &value) {
    version = value;
}

QDateTime DatabaseMigration::getApplyTime() const {
    return applyTime;
}

void DatabaseMigration::setApplyTime(const QDateTime &value) {
    applyTime = value;
}



