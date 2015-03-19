/*
    OpenTeacherTool, a platform independent tool for schoolteacher
    Copyright (C) 2013  Yves Bodenheimer, Christian Ehringfeld, David Mock
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PERSISTENCETYPE_H
#define PERSISTENCETYPE_H
#include <QObject>
#include <QMap>
#include <QString>

namespace OpenTeacherTool {
enum PersistenceType {
    LOCAL=0,
    XML=1,
    REMOTEDATABASE=2
};

static QMap<PersistenceType, QString> initMap() {
    QMap<PersistenceType, QString> map;
    map[LOCAL] = QObject::tr("LocalDatabase");
    map[XML] = QObject::tr("XMLFile");
    map[REMOTEDATABASE] = QObject::tr("RemoteDatabase");
    return map;
}

static QString toString(const PersistenceType &type) {
    static QMap<PersistenceType, QString> map = initMap();
    return map[type];
}

}

#endif // PERSISTENCETYPE_H
