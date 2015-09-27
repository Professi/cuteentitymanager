# CuteEntityManager for Qt

## English
With CuteEntityManager it is possible to persist, merge, find or delete 
entities. Its functionality is based on JPA's EntityManager. For a 
different application I was in search of an easy-to-use ORM. Those particular libraries had either additional dependencies, a smaller 
functional range, were too "complicated" to use (imho) or bound to 
specific platforms.

CuteEntityManager basically supports all platforms supported by Qt. 
Because I am a Java & PHP developer for a living, CuteEntityManager is 
conceptionally based on the aforementioned EntityManager of JPA and in 
parts on the PHP Yii framework.

CuteEntityManager builds solely on Qt/C++ techniqes. The properties for 
the ORM are established by the usage of Q_PROPERTY macros. It is 
possible to use inheritance. Of course, relations (ONE_TO_ONE, 
MANY_TO_ONE, ONE_TO_MANY and MANY_TO_MANY) are also possible. To 
simplify SELECT statements there is a Query API. Thus, it's possible to 
implement a whole application with database connection without using a 
single bit of SQL. Of course, you should be aware of the "specifics" of 
a relational database (notably in matters of relations). Currently, only 
SQLite support is passably tested. Extensions for MySQL/PGSQL/MSSQL 
should be possible quite smoothly.

CuteEntityManager is definitely far from a proper (and tested) or even 
finished state, but because of its use for the creation of another 
application, surely this state will successively improve. Criticism, 
praise, improvement suggestions, pull requests and code reviews are 
welcome at any time. You can reach me directly by mail under
c.ehringfeld[at]t-online.de.

### Features

- sql table creation based on the Q_PROPERTY macro
- relational tables can be generated based on getRelations() method (/* hash.insert("addresses", CuteEntityManager::Relation("addresses",RelationType::MANY_TO_MANY))  */ -> creates table "person_addresses"
- eager data fetch
- CRUD operations with simple method calls (e.g. entitymanager->create(sharedPtr);)
- query api (object-oriented method for building SQL queries)
- Object-Relational Mapping (ORM)
- Multiple instances
(- every Database Entity must inherit from CuteEntityManager::Entity)

Updated daily doxygen documentation:
http://jenkins.danfai.de/jenkins/job/cuteentitymanager/doxygen/
Tutorial(wip):
https://synlos.net/redmine/projects/entitymanager/wiki/Tutorial

### Minimum requirements

- GCC 4.8 or clang 3.3
- >= Qt 5.4
- any platform supported by Qt

## German
Mit dem CuteEntityManager ist es möglich, Entities zu persistieren, zu 
mergen, zu finden und zu löschen. Die Funktionalität ist dem 
EntityManager der JPA nachempfunden. Für eine andere Anwendung war ich 
auf der Suche nach einem leicht zu benutzenden ORM. Entweder enthielten 
die jeweiligen Librarys zusätzliche Abhängigkeiten, hatten nicht den 
gewünschten Funktionsumfang, waren in der Benutzung zu 
"kompliziert"(imho) oder an bestimmte Plattformen gekoppelt.

Der CuteEntityManager unterstützt grundsätzlich alle von Qt 
unterstützten Plattformen. Da ich hauptberuflich Java & PHP Entwickler 
bin, ist der CuteEntityManager dem o.g. EntityManager der JPA und zum 
Teil dem PHP Yii Framework nachempfunden.

Der CuteEntityManager basiert ausschließlich auf Qt/C++ Techniken. Die
Properties für das ORM werden anhand von Q_PROPERTY Makros festgelegt. 
Es ist möglich Vererbung zu nutzen. Relationen (ONE_TO_ONE, MANY_TO_ONE, 
ONE_TO_MANY und MANY_TO_MANY) sind natürlich auch möglich. Um SELECT 
Statements zu vereinfachen, gibt es eine Query API. Man kann also ohne 
ein Stückchen SQL eine komplette Anwendung mit SQL-Datenbank Anbindung 
implementieren. Man sollte sich natürlich über die "Besonderheiten" 
einer relationalen Datenbank im Klaren sein (insbesondere eben bei 
Relationen). Aktuell ist nur die SQLite Unterstützung einigermaßen 
getestet. Erweiterungen für MySQL/PGSQL/MSSQL sollten relativ problemlos 
möglich sein.

Der CuteEntityManager ist sicherlich weit davon entfernt, in einem guten 
(getesteten) bzw. fertigen Zustand zu sein, da er aber für die 
Entwicklung einer anderen Anwendung genutzt wird, wird sich der Zustand 
sicherlich fortlaufend verbessern. Kritik, Lob, Verbesserungsvorschläge, 
Pull Requests, Code Reviews sind jederzeit willkommen. Man kann mich auf 
direktem Wege per Mail an c.ehringfeld[at]t-online.de erreichen.

