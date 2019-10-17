#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
//------------------------------------- data type declaration section [001]
typedef struct syntax* adrsyntax;

typedef struct user* adruser;
typedef struct db* adrdb;
typedef struct table* adrtable;
typedef struct kolom* adrkolom;
typedef struct row* adrrow;
typedef struct isi*  adrisi;

struct syntax{
    string isi;
    adrsyntax next;
};
struct user{
    string username;
    string password;
    adruser next;
    adrdb data;
};
struct db{
    string namadb;
    adrtable first_table;
    adrdb next;
};
struct table{
    string namatabel;
    adrkolom first_kolom;
    adrrow first_row;
    adrtable next;
};
struct kolom{
    string namakolom;
    adrkolom next;
    adrisi first_isi;
};
struct row{
    int rowno;
    adrisi first_isi;
    adrrow next;

};
struct isi{
    string info;
    adrisi next_col;
    adrisi next_row;
    adrisi prev_col;
    adrisi prev_row;
};
struct llist{
    adruser first;
};

//------------------------------------------- allocation section [002]
adrsyntax alokasisyntax(string isi);
adruser alokasiuser(string username, string password);
adrdb alokasidb(string nama);
adrtable alokasitable(string nama);
adrkolom alokasikolom(string nama);
adrrow alokasirow(int rowno);
adrisi alokasiisi(string info);

//------------------------------------------- insert section [003]
void insertsyntax(adrsyntax *s, string isi);
void insertuser(llist *l,string username, string password);
void insertdb(adruser u,string name);
void insertable(adrdb d,string name);
void insertkolom(adrtable t, string name);
void insertrow(adrtable t, int no);
void insertisi(adrkolom k, adrrow r, string info);

//------------------------------------------- delete section [004]
void deletesyntax(adrsyntax *s);
void emptysyntax(adrsyntax *s);
void deletefirstisi(adrrow *r);
void emptyisi(adrrow *r);
void deletefromrow(adrdb *d, string tablename , string kolomcond, string isidel);
void deletefirstrow(adrdb *d, string tablename);
void truncatetable(adrdb *d, string tablename);
void deletefirstkolom(adrdb *d, string tablename);
void emptykolom(adrdb *d, string tablename);
void droptable(adrdb *d , string tablename);
//------------------------------------------- search section [005]
adruser searchuser(llist l,string username);
adrdb searchdb(adruser a, string dbname);
adrtable searchtable(adrdb a, string tablename);
adrkolom searchkolom(adrtable a, string kolomname);
adrrow searchrow(adrtable a, int rowno);
adrisi searchisi(adrkolom a, string isinya);
//------------------------------------------- Aljabar Relational  Section [006]
void printsyntax(adrsyntax s);
void createtable(adrdb a,string tablename);
void createkolom(adrtable a,string kolomname);
int countrow(adrtable t);
void createrow(adrtable t, int rowno);
void viewall(adrtable a);
void sorttable(adrdb d, string tablename, string kolomby);
void viewdesctable(adrdb d, string tablename);
void updateisi(adrdb d, string tablename , string koldestin , string isidestin , string kolcond, string isicond);
//------------------------------------------- ----------------------------------syntax  section [007]
adrsyntax selector();

bool is_create(adrsyntax s);
adrsyntax syntaxofcreate(adrsyntax s);
void executecreate(adrsyntax s, adrdb *l);

bool is_insert(adrsyntax s);
adrsyntax syntaxofinsert(adrsyntax s, adrdb l);
void executeinsert(adrsyntax s,adrdb *l);

bool is_selectall_nowhere_nosort(adrsyntax s);
adrsyntax syntaxofselectallnowherenosort(adrsyntax s, adrdb d);
void executeselectallnowherenosort(adrsyntax s, adrdb d);

bool is_selectall_nowhere_sort(adrsyntax s);
adrsyntax syntaxofselectallnowheresort(adrsyntax s, adrdb d);
void executeselectallnowheresort(adrsyntax s , adrdb d);

bool is_deletefrom(adrsyntax s);
adrsyntax syntaxofdeletefrom(adrsyntax s, adrdb d);
void executedeletesyntax(adrsyntax s, adrdb *d);

bool is_truncatetable(adrsyntax s);
adrsyntax syntaxoftruncate(adrsyntax s, adrdb d);
void executetruncate(adrsyntax s, adrdb *d);

bool is_drop(adrsyntax s);
adrsyntax syntaxofdrop(adrsyntax s, adrdb d);
void executedrop(adrsyntax s, adrdb *d);

bool is_desc(adrsyntax s);
adrsyntax syntaxofdesc(adrsyntax s,adrdb d);
void executedesc(adrsyntax s, adrdb d);

bool is_update(adrsyntax s);
adrsyntax syntaxofupdate(adrsyntax s, adrdb d);
void executeupdate(adrsyntax s, adrdb d);

void executor(adrdb *l, adrsyntax root, int *dec);

#endif // HEADER_H_INCLUDED
