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
#include "sqlitebackupprocessor.h"
#include <sqlite3.h>

using namespace CuteEntityManager;
SqliteBackupProcessor::SqliteBackupProcessor(QSharedPointer<Database> database,
        QString destination) : QObject() {
    this->database = database;
    this->destination = destination;
}

SqliteBackupProcessor::~SqliteBackupProcessor() {
}

QSharedPointer<Database> SqliteBackupProcessor::getDatabase() const {
    return database;
}

void SqliteBackupProcessor::setDatabase(const QSharedPointer<Database> &value) {
    database = value;
}
QString SqliteBackupProcessor::getDestination() const {
    return destination;
}

void SqliteBackupProcessor::setDestination(const QString &value) {
    destination = value;
}

/**
 * @see http://www.qtcentre.org/threads/36131-Attempting-to-use-Sqlite-backup-api-from-driver-handle-fails
 * @brief SqliteBackupProcessor::backup
 * @param fileName
 * @return
* This function is used to load the contents of a database file on disk
* into the "main" database of open database connection pInMemory, or
* to save the current contents of the database opened by pInMemory into
* a database file on disk. pInMemory is probably an in-memory database,
* but this function will also work fine if it is not.
*
* Parameter zFilename points to a nul-terminated string containing the
* name of the database file on disk to load from or save to. If parameter
* isSave is non-zero, then the contents of the file zFilename are
* overwritten with the contents of the database opened by pInMemory. If
* parameter isSave is zero, then the contents of the database opened by
* pInMemory are replaced by data loaded from the file zFilename.
*
* If the operation is successful, SQLITE_OK is returned. Otherwise, if
* an error occurs, an SQLite error code is returned.
*/
bool SqliteBackupProcessor::sqliteDBMemFile(bool save, QString fileName) {
    bool state = false;
    QVariant v = this->database->getDatabase().driver()->handle();
    if ( v.isValid() && qstrcmp(v.typeName(), "sqlite3*") == 0 ) {
        // v.data() returns a pointer to the handle
        sqlite3 *handle = *static_cast<sqlite3 **>(v.data());
        if ( handle != 0 ) { // check that it is not NULL
            sqlite3 *pInMemory = handle;
            QByteArray array = QString(this->destination + "/" + fileName).toLocal8Bit();
            const char *zFilename = array.data();
            int rc;                   /* Function return code */
            sqlite3 *pFile;           /* Database connection opened on zFilename */
            sqlite3_backup *pBackup;  /* Backup object used to copy data */
            sqlite3 *pTo;             /* Database to copy to (pFile or pInMemory) */
            sqlite3 *pFrom;           /* Database to copy from (pFile or pInMemory) */

            /* Open the database file identified by zFilename. Exit early if this fails
            ** for any reason. */
            rc = sqlite3_open( zFilename, &pFile );
            if ( rc == SQLITE_OK ) {
                /* If this is a 'load' operation (isSave==0), then data is copied
                ** from the database file just opened to database pInMemory.
                ** Otherwise, if this is a 'save' operation (isSave==1), then data
                ** is copied from pInMemory to pFile.  Set the variables pFrom and
                ** pTo accordingly. */
                pFrom = ( save ? pInMemory : pFile);
                pTo   = ( save ? pFile     : pInMemory);
                /* Set up the backup procedure to copy from the "main" database of
                ** connection pFile to the main database of connection pInMemory.
                ** If something goes wrong, pBackup will be set to NULL and an error
                ** code and  message left in connection pTo.
                **
                ** If the backup object is successfully created, call backup_step()
                ** to copy data from pFile to pInMemory. Then call backup_finish()
                ** to release resources associated with the pBackup object.  If an
                ** error occurred, then  an error code and message will be left in
                ** connection pTo. If no error occurred, then the error code belonging
                ** to pTo is set to SQLITE_OK.
                */
                pBackup = sqlite3_backup_init(pTo, "main", pFrom, "main");
                if ( pBackup ) {
                    (void)sqlite3_backup_step(pBackup, -1);
                    (void)sqlite3_backup_finish(pBackup);
                }
                rc = sqlite3_errcode(pTo);
            }
            /* Close the database connection opened on database file zFilename
            ** and return the result of this function. */
            (void)sqlite3_close(pFile);
            if ( rc == SQLITE_OK ) {
                state = true;
            }
        }
    }
    return state;
}
