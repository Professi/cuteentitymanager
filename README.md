# CuteEntityManager for Qt
## German
Mit dem CuteEntityManager ist es möglich Entities zu persistieren, zu mergen, zu finden und zu löschen. Die Funktionalität ist dem EntityManager der JPA nachempfunden. Für eine Anwendung war ich auf der Suche nach einem leicht zu benutzenden ORM. Entweder enthielt die jeweilige Library zusätzliche Abhängigkeiten, hatte nicht den gewünschten Funktionsumfang, war in der Benutzung zu "kompliziert"(imho) oder war nur an bestimmte Plattformen gekoppelt. Der CuteEntityManager unterstützt grundsätzlich alle von Qt unterstützten Plattformen. Da ich hauptberuflich Java & PHP Entwickler bin, ist der CuteEntityManager dem o.g. EntityManager der JPA und zum Teil dem PHP Yii Framework nachempfunden.
Der CuteEntityManager basiert ausschließlich auf Qt/C++ Techniken. Der Properties für das ORM werden anhand von Q_PROPERTY Makros festgelegt. Es ist möglich Vererbung zu nutzen. Relationen (ONE_TO_ONE, MANY_TO_ONE, ONE_TO_MANY und MANY_TO_MANY) sind natürlich auch möglich. Um SELECT Statements zu vereinfachen gibt es eine Query API. Man kann also ohne ein Stückchen SQL eine komplette Anwendung mit SQL Datenbank Anbindung implementieren. Man sollte sich natürlich über die "Besonderheiten" einer relationalen Datenbank im Klaren sein (insbesondere eben bei Relationen). Aktuell ist nur einigermaßen die SQLite Unterstützung getestet. Eine Erweiterung für MySQL/PGSQL/MSSQL sollte relativ problemlos möglich sein.

Der CuteEntityManager ist sicherlich weit davon entfernt in einem guten (getesteten) bzw. fertigen Zustand zu sein, da er aber für die Entwicklung einer anderen Anwendung genutzt wird, wird sich der Zustand sicherlich fortlaufend verbessern. Kritik, Lob, Verbesserungsvorschläge, Pull Requests, Code Reviews sind jederzeit Willkommen. Man kann mich auf direktem Wege per Mail an c.ehringfeld[at]t-online.de erreichen.

## English
tbc.
