#include "createfakemodeldata.h"
#include "../person.h"
#include "../pupil.h"
#include "../address.h"
#include "../contact.h"
#include "../group.h"

void CreateFakeModelData::fillGroup(Group* group) {
    group->addPerson(new Person("Tim","Berg",Person::Gender::MALE,"Tim Berg.jpg",QString(),QString(),QDate(2000,7,13),0));
    group->addPerson(new Person("Lena","Conrad",Person::Gender::FEMALE,"Lena Conrad.jpg",QString(),QString(),QDate(2000,7,13),0));
    group->addPerson(new Person("Marcel","Dunst",Person::Gender::MALE,"Marcel Dunst.jpg",QString(),QString(),QDate(2000,7,13),0));

    group->addPupil(new Pupil("Tim","Berg",Person::Gender::MALE,"Tim Berg.jpg",QString(),QString(),QDate(2000,7,13),"05c",0));
    group->addPupil(new Pupil("Lena","Conrad",Person::Gender::FEMALE,"Lena Conrad.jpg",QString(),QString(),QDate(2000,7,13),"05c",0));
    group->addPupil(new Pupil("Marcel","Dunst",Person::Gender::MALE,"Marcel Dunst.jpg",QString(),QString(),QDate(2000,7,13),"05c",0));
    group->addPupil(new Pupil("Carsten","Ernst",Person::Gender::MALE,"Carsten Ernst.jpg",QString(),QString(),QDate(2000,7,13),"05c",0));
    group->addPupil(new Pupil("Hannah","Eschborn",Person::Gender::FEMALE,"Hannah Eschborn.jpg",QString(),QString(),QDate(2000,7,13),"05c",0));
    group->addPupil(new Pupil("Vera","Geseke",Person::Gender::FEMALE,"Vera Geseke.jpg",QString(),QString(),QDate(2000,4,1),"05c",0));
    group->addPupil(new Pupil("Jann","Hagedorn",Person::Gender::MALE,"Jann Hagedorn.jpg",QString(),QString(),QDate(2000,8,16),"05c",0));
    group->addPupil(new Pupil("Svenja","Hartmann",Person::Gender::FEMALE,"Svenja Hartmann.jpg",QString(),QString(),QDate(2000,2,2),"05c",0));
    group->addPupil(new Pupil("Timo","Haufer",Person::Gender::MALE,"Timo Haufer.jpg",QString(),QString(),QDate(2000,2,28),"05c",0));
    group->addPupil(new Pupil("Birthe","Jäger",Person::Gender::FEMALE,"Birthe Jaeger.jpg",QString(),QString(),QDate(2000,2,14),"05c",0));

    group->pupilAt(0)->addAddress(new Address("Erzieher","Bukesweg 473","33330","Gütersloh"));
    group->pupilAt(1)->addAddress(new Address("Erzieher","Bukesweg 473","33330","Gütersloh"));
    group->pupilAt(2)->addAddress(new Address("Erzieher","Bukesweg 473","33330","Gütersloh"));
    group->pupilAt(3)->addAddress(new Address("Erzieher","Bukesweg 473","33330","Gütersloh"));
    group->pupilAt(4)->addAddress(new Address("Erzieher","Bukesweg 473","33330","Gütersloh"));
    group->pupilAt(5)->addAddress(new Address("Erzieher","Auguste-Viktoria-Platz 193","77652","Offenburg"));
    group->pupilAt(6)->addAddress(new Address("Erzieher","Bullenwinkel 467","74074","Heilbronn"));
    group->pupilAt(7)->addAddress(new Address("Erzieher","Schinkelplatz 389","46236","Bottrop"));
    group->pupilAt(8)->addAddress(new Address("Erzieher","Mentzelstraße 327","33617","Bielefeld"));
    group->pupilAt(9)->addAddress(new Address("Erzieher","Bundesallee 252","49082","Osnabrück"));

    group->pupilAt(0)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-474466"));
    group->pupilAt(1)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-474466"));
    group->pupilAt(2)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-474466"));
    group->pupilAt(3)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-474466"));
    group->pupilAt(4)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-474466"));
    group->pupilAt(5)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-340678"));
    group->pupilAt(6)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-697259"));
    group->pupilAt(7)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-893457"));
    group->pupilAt(8)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-329887"));
    group->pupilAt(9)->addContact(new Contact("Telefon 1",Contact::Category::LANDLINE,"01234-929597"));

    group->pupilAt(0)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-755490"));
    group->pupilAt(1)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-755490"));
    group->pupilAt(2)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-755490"));
    group->pupilAt(3)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-755490"));
    group->pupilAt(4)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-755490"));
    group->pupilAt(5)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-791688"));
    group->pupilAt(6)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-837199"));
    group->pupilAt(7)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-194122"));
    group->pupilAt(8)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-145996"));
    group->pupilAt(9)->addContact(new Contact("Telefon 2",Contact::Category::LANDLINE,"01234-446435"));

    group->pupilAt(0)->addContact(new Contact("Email",Contact::Category::EMAIL,"TimmieB@smail.de_"));
    group->pupilAt(1)->addContact(new Contact("Email",Contact::Category::EMAIL,"lenalenalena3@smail.de_"));
    group->pupilAt(2)->addContact(new Contact("Email",Contact::Category::EMAIL,"marcel.dunst111@smail.de_"));
    group->pupilAt(3)->addContact(new Contact("Email",Contact::Category::EMAIL,"cernst@smail.de_"));
    group->pupilAt(4)->addContact(new Contact("Email",Contact::Category::EMAIL,"hannahsemail@smail.de_"));
    group->pupilAt(5)->addContact(new Contact("Email",Contact::Category::EMAIL,"vrgsk@smail.de_"));
    group->pupilAt(6)->addContact(new Contact("Email",Contact::Category::EMAIL,"hagedornjann@smail.de_"));
    group->pupilAt(7)->addContact(new Contact("Email",Contact::Category::EMAIL,"svenja_H@smail.de_"));
    group->pupilAt(8)->addContact(new Contact("Email",Contact::Category::EMAIL,"dertimohatmail@smail.de_"));
    group->pupilAt(9)->addContact(new Contact("Email",Contact::Category::EMAIL,"birthe-hunter@smail.de_"));

    group->pupilAt(0)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"info@berg-immobilien.com_"));
    group->pupilAt(1)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"ClemensundAnja@DieConrads.de_"));
    group->pupilAt(2)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"sales@dunst-aufzuege.de_"));
    group->pupilAt(3)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"FamilieErnst@smail.de_"));
    group->pupilAt(4)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"juergen.eschborn@smail.de_"));
    group->pupilAt(5)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"Britta_Geseke@smail.de_"));
    group->pupilAt(6)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"familie@hagedorns.de_"));
    group->pupilAt(7)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"hartmaenner@smail.de_"));
    group->pupilAt(8)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"Marco.Haufer@email.de_"));
    group->pupilAt(9)->addContact(new Contact("Email Eltern",Contact::Category::EMAIL,"aufzumfroehlichenjagen@email.de_"));
}
