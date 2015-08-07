#include "sqlitebackupprocessor.h"
#include "sqlite3.h"

using namespace CuteEntityManager;
SqliteBackupProcessor::SqliteBackupProcessor(QSharedPointer<Database> database,
        QString destination) {
    this->database = database;
    this->destination = destination;
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

bool SqliteBackupProcessor::backup(QString fileName = "db.sqlite.bak") {
    bool state = false;
    bool save = true;
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



