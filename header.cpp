#include "header.h"

//------------------------------------------- allocation section [002]
adrsyntax alokasisyntax(string isi){
    adrsyntax p;
    p = new syntax;
    p->isi = isi;
    p->next = NULL;
    return p;
};
adruser alokasiuser(string username, string password){
    adruser p;
    p = new user;
    p->next = NULL;
    p->data = NULL;
    p->username = username;
    p->password = password;
    return p;
};
adrdb alokasidb(string nama){
    adrdb p;
    p = new db;
    p->next = NULL;
    p->first_table = NULL;
    p->namadb = nama;
    return p;

};
adrtable alokasitable(string nama){
    adrtable p;
    p = new table;
    p->next = NULL;
    p->first_row = NULL;
    p->first_kolom = NULL;
    p->namatabel = nama;
    return p;
};
adrkolom alokasikolom(string nama){
    adrkolom p;
    p = new kolom;
    p->next = NULL;
    p->first_isi = NULL;
    p->namakolom = nama;
    return p;

};
adrrow alokasirow(int rowno){
    adrrow p;
    p = new row;
    p->rowno = rowno;
    p->next = NULL;
    p->first_isi = NULL;
    return p;
};
adrisi alokasiisi(string info){
    adrisi p;
    p = new isi;
    p->next_row = NULL;
    p->next_col = NULL;
    p->prev_col = NULL;
    p->prev_row = NULL;
    p->info = info;
    return p;
};
//------------------------------------------- insert section [003]
void insertsyntax(adrsyntax *s, string isi){
    adrsyntax p,h;
    p = alokasisyntax(isi);
    if(*s==NULL){*s=p;}
    else{
        h = *s;
        while(h->next!=NULL){h = h->next;}
        h->next =p;
    }
};
void insertuser(llist *l,string username, string password){
    adruser p,h;
    p = alokasiuser(username,password);
    if(l->first==NULL){l->first=p;}
    else{
        h = l->first;
        while(h->next!=NULL){h = h->next;}
        h->next = p;
    }
};
void insertdb (adruser u,string name){
    adrdb p,h;
    p = alokasidb(name);
    if(u->data==NULL){u->data = p;}
    else{
        h = u->data;
        while(h->next!=NULL){h = h->next;}
        h->next = p;
    }
};
void insertable(adrdb d,string name){
    adrtable p,h;
    p = alokasitable(name);
    if(d->first_table==NULL){d->first_table = p;}
    else{
        h = d->first_table;
        while(h->next!=NULL){h = h->next;}
        h->next = p;
    }
};
void insertkolom(adrtable t, string name){
    adrkolom p,h;
    p = alokasikolom(name);
    if(t->first_kolom==NULL){t->first_kolom = p;}
    else{
        h = t->first_kolom;
        while(h->next!=NULL){h = h->next;}
        h->next = p;
    }
};
void insertrow(adrtable t, int no){
     adrrow p,h;
    p = alokasirow(no);
    if(t->first_row==NULL){t->first_row = p;}
    else{
        h = t->first_row;
        while(h->next!=NULL){h = h->next;}
        h->next = p;
    }
};
void insertisi(adrkolom k, adrrow r, string info){
    adrisi p,h,h2;
    p = alokasiisi(info);
    if(k->first_isi==NULL){k->first_isi = p;}
    else{
        h = k->first_isi;
        while(h->next_row!=NULL){h = h->next_row;}
        p->prev_row = h;
        h->next_row = p;
    }

    if(r->first_isi==NULL){r->first_isi = p;}
    else{
        h2 = r->first_isi;
        while(h2->next_col!=NULL){h2 = h2->next_col;}
        p->prev_col = h2;
        h2->next_col = p;
    }
};


//------------------------------------------- delete section [004]
void deletesyntax(adrsyntax *s){
    adrsyntax p;
    p = *s;
    if(p->next==NULL){ *s = NULL ; delete p;}
    else if(*s!=NULL){
        p = *s;
        *s = (*s)->next;
        p->next = NULL;
        delete p;
    }
};
void emptysyntax(adrsyntax *s){
    while(*s!=NULL){
        deletesyntax(s);
    }

};

void deletefirstisi(adrrow *r){
    adrisi i;
    i = (*r)->first_isi;
    if(i->next_col==NULL){(*r)->first_isi = NULL; delete i;}
    else if(i!=NULL){
        (*r)->first_isi = i->next_col;
        i->next_col->prev_col = NULL;
        i->next_col = NULL;
        delete i;
    }
};

void emptyisi(adrrow *r){
    while((*r)->first_isi!=NULL){
        deletefirstisi(&(*r));
    }
    delete *r;
}

void deletefromrow(adrdb *d, string tablename , string kolomcond, string isidel){
    adrtable t; adrkolom k,ka; adrisi i,agenrow; adrrow r,ro,re;
    t = searchtable(*d,tablename);
    k = searchkolom(t,kolomcond);
    i = searchisi(k,isidel);
    r = t->first_row;
    while(i->prev_col!=NULL){i = i->prev_col;}
    re = r;
    if(r!=NULL){

        if(r->first_isi!=i){
            while(re->next->first_isi!= i){re = re->next;}
            ro = re->next;

            if(ro->next==NULL){
                agenrow = ro->first_isi;
                i = re->first_isi;
                while(i!=NULL){
                    agenrow->prev_row = NULL;
                    i->next_row = NULL;
                    agenrow = agenrow->next_col;
                    i = i->next_col;
                }
                re->next = NULL;
                emptyisi(&ro);
            }
             else{
        agenrow = ro->first_isi;
        i = re->first_isi;
        while(i!=NULL){
            i->next_row = agenrow->next_row;
            agenrow->next_row->prev_row = i;
            agenrow->prev_row = NULL;
            agenrow->next_row = NULL;

            agenrow = agenrow->next_col;
            i = i->next_col;
        }
        re->next = ro->next;
        ro->next = NULL;
        emptyisi(&ro);

    }
        re = re->next;
        while(re!=NULL){
            re->rowno = re->rowno - 1;
            re = re->next;
        }
    }
        else if(r->first_isi == i){

        if(r->next==NULL){
        ka = t->first_kolom;
        while(ka!=NULL){
        ka->first_isi = NULL;
        ka = ka->next;
        }
        t->first_row = NULL;
        emptyisi(&r);
        }
            else{
            t->first_row = t->first_row->next;
            r->next = NULL;
        //
            ka = t->first_kolom;
            while(ka!=NULL){
                agenrow = ka->first_isi;
                ka->first_isi  = ka->first_isi->next_row;
                agenrow->next_row->prev_row = NULL;
                agenrow->next_row = NULL;
                ka = ka->next;
        }
        emptyisi(&r);
        re = t->first_row;
        while(re!=NULL){
            re->rowno = re->rowno - 1;
            re = re->next;

        }
        }

    }

    }
};

void deletefirstrow(adrdb *d, string tablename){
    adrtable t; adrrow r ; adrkolom k; adrisi i;
    t = searchtable(*d,tablename);
    if(t!=NULL){
        r = t->first_row;
        k = t->first_kolom;
        if(r->next==NULL){
                t->first_row=NULL;
                while(k!=NULL){
                    k->first_isi = NULL;
                    k = k->next;
                }
                emptyisi(&r);

        }
        else{
            t->first_row = t->first_row->next;
            r->next = NULL;
            i = r->first_isi;
            while(k!=NULL){

                k->first_isi = k->first_isi->next_row;
                i->next_row->prev_row = NULL;
                i->next_row = NULL;

                i = i->next_col;
                k = k->next;
            }

            emptyisi(&r);

        }
    }
};

void truncatetable(adrdb *d, string tablename){
    adrtable t;
    t = searchtable(*d,tablename);
    while(t->first_row!=NULL){
        deletefirstrow(&(*d),tablename);
    }
};

void deletefirstkolom(adrdb *d, string tablename){
    adrtable t; adrkolom k;
    t = searchtable(*d,tablename);
    k = t->first_kolom;
    if(k->next==NULL){ t->first_kolom = NULL; delete k;
    }
    else{
        t->first_kolom = t->first_kolom->next;
        k->next = NULL;
        delete k;
    }
};

void emptykolom(adrdb *d, string tablename){
    adrtable t;
    t = searchtable(*d,tablename);
    while(t->first_kolom!=NULL){
        deletefirstkolom(d,tablename);
    }
};

void droptable(adrdb *d , string tablename){
    adrtable t,ta; adrkolom k;
    t = searchtable(*d, tablename);
    if(t!=NULL){
        truncatetable(d,tablename);
        emptykolom(d,tablename);
        ta = (*d)->first_table;
        if(ta==t){(*d)->first_table = NULL; delete t;}
        else if(t->next == NULL){
            while(ta->next!=t){
                ta = ta->next;
            }
            ta->next = NULL;
            delete t;
        }
        else {
            while(ta->next!=t){
                ta = ta->next;
            }
            ta->next = t->next;
            t->next = NULL;
            delete t;
        }
    }
};

//------------------------------------------- search section [005]
adruser searchuser(llist l,string username){
    adruser p,found=NULL;
    p = l.first;
    while(p!=NULL){
        if(p->username == username){found = p;}
        p = p->next;
    }
    return found;
};
adrdb searchdb(adruser a, string dbname){
    adrdb p,found=NULL;
    p = a->data;
    while(p!=NULL){
        if(p->namadb == dbname){found = p;}
        p = p->next;
    }
    return found;
};
adrtable searchtable(adrdb a, string tablename){
    adrtable p,found=NULL;
    p = a->first_table;
    while(p!=NULL){
        if(p->namatabel == tablename){found = p;}
        p = p->next;
    }
    return found;


};
adrkolom searchkolom(adrtable a, string kolomname){
    adrkolom p,found=NULL;
    p = a->first_kolom;
    while(p!=NULL){
        if(p->namakolom == kolomname){found = p;}
        p = p->next;
    }
    return found;

};
adrrow searchrow(adrtable a, int rowno){
    adrrow p, found = NULL;
    p = a->first_row;
    while(p!=NULL){
        if(p->rowno == rowno){found = p;}
        p = p->next;
    }
    return found;
}
adrisi searchisi(adrkolom a, string isinya){
    adrisi p,found=NULL;
    p = a->first_isi;
    while(p!=NULL){
        if(p->info == isinya){found = p;}
        p = p->next_row;
    }
    return found;

};

//------------------------------------------- Aljabar Relational  Section [006]
void printsyntax(adrsyntax s){
    adrsyntax h;
    h=s;
    while(h!=NULL){
        cout<< h->isi << endl;
        h=h->next;
    }
};
void createtable(adrdb a,string tablename){
    adrtable p;
    p = searchtable(a,tablename);
    if(p!=NULL){cout<<endl<<"Table sudah ada"<<endl;}
    else{
        insertable(a,tablename);
    }
};
void createkolom(adrtable a,string kolomname){
    adrkolom p;
    p = searchkolom(a,kolomname);
    if(p!=NULL){cout<<endl<<"Kolom Sudah tersedia";}
    else{
        insertkolom(a,kolomname);
    }
};
int countrow(adrtable t){
    adrrow r;int m=0;
    r = t->first_row;
    while(r!=NULL){
        m++;
        r = r->next;
    }
    return m+1;
}
void createrow(adrtable t, int rowno){
    adrrow r;
    r = searchrow(t,rowno);
    if(r!=NULL){cout<< "row sudah ada"<<endl;}
    else{
        insertrow(t,rowno);
    }
};
void viewall(adrtable a){
    adrkolom p;
    adrisi k;
    adrrow r;
    if(a!=NULL){
    p = a->first_kolom;
    while(p!=NULL){
        cout << p->namakolom << "    ||";
        p = p->next;
    }
    cout<<endl;
    for(int ma = 1; ma<=77; ma++){cout<<"-";}
    cout<< endl;
    r = a->first_row;
    p = a->first_kolom;
    while(r!=NULL){
        k = r->first_isi;
        while(k!=NULL){
            cout << k->info << "---------------";
            k = k->next_col;
        }
    r = r->next;
    cout<< endl;
    }
    }
}
void sorttable(adrdb d, string tablename, string kolomby){
    adrrow r=NULL,currentr; adrtable t; adrkolom k,ka,temp=NULL,ki=NULL; adrisi tempisi=NULL, i, m,n,mins,shadowi;
    t = searchtable(d,tablename);
    if(t!=NULL){
        k = searchkolom(t,kolomby);
        if(k!=NULL){
            r = alokasirow(0);//bikin row temporary
            currentr = t->first_row;
            tempisi = currentr->first_isi;
            temp = t->first_kolom;
            while(tempisi!=NULL){
                ki = NULL;
                ki = alokasikolom(temp->namakolom);
                if(temp==t->first_kolom){ka = ki;}
                insertisi(ki,r,tempisi->info);
                tempisi = tempisi->next_col;

            }//temp row created

            m = k->first_isi;
            while(m!=NULL){
                n = m;
                mins = m;
                shadowi = r->first_isi;
                while(n!=NULL){
                if(n->info < mins->info){mins = n;}
                n = n->next_row;
                }
                tempisi = mins; while(tempisi->prev_col!=NULL){tempisi = tempisi->prev_col;}
                i = m; while(i->prev_col!=NULL){i = i->prev_col;}
                while(i!=NULL){
                    shadowi->info = tempisi->info;
                    tempisi->info = i->info;
                    i->info = shadowi->info;

                    shadowi = shadowi->next_col;
                    i = i->next_col;
                    tempisi = tempisi->next_col;
                }
            m = m->next_row;
            }
        }
    }
};
void viewdesctable(adrdb d, string tablename){
    adrtable t; adrkolom k;
    t = searchtable(d,tablename);
    k = t->first_kolom;
    cout<< "ATRIBUT TABLE " << tablename<<endl;
    cout<< "====================================================================================================="<<endl;
    while(k!=NULL){
        cout<<"|| ";
        cout<< k->namakolom<<endl;
        k = k->next;
    }
};
void updateisi(adrdb d, string tablename , string koldestin , string isidestin , string kolcond, string isicond){
    adrtable t;
    adrkolom dkolom, ckolom;
    adrisi icond, idestin;
    t = searchtable(d,tablename);
    ckolom = searchkolom(t,kolcond);
    dkolom = searchkolom(t,koldestin);
    icond = ckolom->first_isi;
    idestin = dkolom->first_isi;
    while(icond->info!=isicond){
        icond=icond->next_row;
        idestin=idestin->next_row;
    }
    idestin->info = isidestin;
};



//------------------------------------------- ----------------------------------syntax  section [007]
adrsyntax selector(){
    bool dec = false;
    string temp;
    adrsyntax s=NULL;
    cout<< "SQL>>";
    while(dec==false){
        cin>> temp;
        insertsyntax(&s,temp);
        if((temp==";")||(temp[temp.length()-1])==';'){dec=true;}
    }
    return s;
};

//create table syntax [S01]
bool is_create(adrsyntax s){
    adrsyntax help; bool p=true;
    help = s;
    if((help->isi!="create")||(help==NULL)){p = false;}
    else{
        help = help->next;
        if((help==NULL)||(help->isi!="table")){p = false;}
        else{
            help = help->next;
            if(help==NULL){p = false;}
            else{
                help = help->next;
                if((help==NULL)||(help->isi!="(")){p = false;}
                else{
                    help = help->next;
                    if(help==NULL){p = false;}
                    else{
                        while((help!=NULL)&&(help->isi!=")")){
                            help = help->next;
                        }
                        if(help==NULL){p = false;}
                        else{
                            help = help->next;
                            if((help==NULL)||(help->isi!=";")){p = false;}
                        }
                    }
                }
            }
        }

    }

    return p;
};
adrsyntax syntaxofcreate(adrsyntax s){
    adrsyntax p,q=NULL;
    if(is_create(s)==true){
        p = s;
        while(p->isi!="table"){p= p->next;}
        p = p->next;
        insertsyntax(&q,p->isi);
        p = p->next->next;
        while(p->isi!=")"){
            insertsyntax(&q,p->isi);
            p = p->next;
        }
        return q;
    }
    else{return NULL;}
};
void executecreate(adrsyntax s, adrdb *l){
    adrsyntax p; adrtable t;
    p = s;
    createtable(*l,p->isi);
    t = searchtable(*l,p->isi);
    p = p->next;
    while(p!=NULL){
        if(p->isi!=",")createkolom(t,p->isi);
        p = p->next;
    }
};
//---------------------------------------------------------------------------

//insert value to table syntax [S02]
bool is_insert(adrsyntax s){
    adrsyntax h; bool p = true;
    h = s;
    if((h->isi!="insert")||(h==NULL)){p = false;}
    else{
        h = h->next;
        if((h==NULL)||(h->isi!="into")){p = false;}
        else{
            h = h->next;
            if(h==NULL){p = false;}
            else{
                h = h->next;
                if((h==NULL)||(h->isi!="values")){p = false;}
                else{
                    h = h->next;
                    if((h==NULL)||(h->isi!="(")){p = false;}
                    else{
                        h = h->next;
                        while((h!=NULL)&&(h->isi!=")")){h = h->next;}
                        if(h==NULL){p=false;}
                        else{
                            h = h->next;
                            if((h==NULL)||(h->isi!=";")){p = false;}

                        }

                    }
                }
            }
        }

    }
return p;
};
adrsyntax syntaxofinsert(adrsyntax s, adrdb l){
    adrsyntax p,q=NULL;
    adrtable t;
    p = s;
    if(is_insert(s)==true){
        while(p->isi!="into"){p = p->next;}
        p = p->next;
        t = searchtable(l,p->isi);
        if(t==NULL){cout<< "tabel tidak ada"; return NULL;}
        else{
            insertsyntax(&q,p->isi);
            p = p->next->next->next;
            while(p->isi!=")"){
                if(p->isi!=","){insertsyntax(&q,p->isi);}
                p = p->next;
            }
            return q;
        }
    }
    else{return NULL;}

};
void executeinsert(adrsyntax s,adrdb *l){
    adrsyntax p;
    adrtable t;
    adrrow r; int rowno;
    adrkolom k;
        p = s;
        t = searchtable(*l,p->isi);
        p = p->next;
        rowno = countrow(t);
        createrow(t,rowno);
        r = searchrow(t,rowno);
        k = t->first_kolom;
        while(p!=NULL){
            insertisi(k,r,p->isi);
            k = k->next;
            p = p->next;
        }


};
//---------------------------------------------------------------------------

//select syntax [S03]
//no sort
bool is_selectall_nowhere_nosort(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="select")){status = false;}
    else{
        p = p->next;
        if((p==NULL)||(p->isi!="*")){status = false;}
        else{
            p = p->next;
            if((p==NULL)||(p->isi!="from")){status = false;}
            else{
                p = p->next;
                if(p==NULL){status = false;}
                else{
                    p = p->next;
                    if((p==NULL)||(p->isi!=";")){status = false;}
                }

            }

        }



    }

    return status;
};
adrsyntax syntaxofselectallnowherenosort(adrsyntax s, adrdb d){
    adrsyntax p, q = NULL;
    adrtable t;
    if(is_selectall_nowhere_nosort(s)==true){
    p = s;
    while(p->isi!="from"){p = p->next;}
    p = p->next;
    t = searchtable(d,p->isi);
    if(t==NULL){cout<< "Tabel tidak ada" << endl; return NULL;}
    else{
        insertsyntax(&q,p->isi);
        return q;
    }

    }
    else{return NULL;}
};
void executeselectallnowherenosort(adrsyntax s, adrdb d){
    adrsyntax p;
    adrtable t;
    p = s;
    t = searchtable(d,p->isi);
    if(t!=NULL){
    viewall(t);
    cout<<endl << countrow(t) - 1 << " rows selected "<<endl;}
    else{cout<< endl<<"syntax salah"<<endl;}
};
//with sort
bool is_selectall_nowhere_sort(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="select")){status = false;}
    else{
        p = p->next;
        if((p==NULL)||(p->isi!="*")){status = false;}
        else{
            p = p->next;
            if((p==NULL)||(p->isi!="from")){status = false;}
            else{
                p = p->next;
                if(p==NULL){status = false;}
                else{
                    p=p->next;
                    if((p==NULL)||(p->isi!="order")){status = false;}
                    else{
                        p = p->next;
                        if ((p==NULL)||(p->isi!="by")){status = false;}
                        else{
                            p = p->next;
                            if (p==NULL){status = false;}
                            else {
                                p = p->next;
                                if((p==NULL)||(p->isi!="asc")){status = false;}
                                else {
                                    p=p->next;
                                    if((p==NULL)||(p->isi!=";")){status = false;}
                                }
                            }
                        }
                    }
                }


            }

        }
    }

    return status;
};
adrsyntax syntaxofselectallnowheresort(adrsyntax s, adrdb d){
     adrsyntax p, q = NULL; adrkolom k;
    adrtable t;
    if(is_selectall_nowhere_sort(s)==true){
    p = s;
    while(p->isi!="from"){p = p->next;}
    p = p->next;
    t = searchtable(d,p->isi);
    if(t==NULL){cout<< "Tabel tidak ada" << endl;}
    else{
        insertsyntax(&q,p->isi);
        p = p->next;
        while(p->isi!="by"){p = p->next;}
        p = p->next;
        k = searchkolom(t,p->isi);
        if(k!=NULL){
        insertsyntax(&q,p->isi);
        return q;
        } else{return NULL;}

    }
    }
    else{return NULL;}
};
void executeselectallnowheresort(adrsyntax s , adrdb d){
    adrsyntax p;
    adrtable t;
    p = s;
    t = searchtable(d,p->isi);
    if(t!=NULL){
        sorttable(d,p->isi,p->next->isi);
        viewall(t);
        cout<<endl << countrow(t) - 1 << " rows selected "<<endl;}
    else{cout<< endl<<"syntax salah"<<endl;}
};
//---------------------------------------------------------------------------

//delete syntax [S04]
bool is_deletefrom(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="delete")){status = false;}
    else{
        p = p->next;
        if((p==NULL)||(p->isi!="from")){status = false;}
        else{
            p = p->next;
            if(p==NULL){status = false;}
            else{
                p = p->next;
                if((p==NULL)||(p->isi!="where")){status = false;}
                else{
                    p = p->next;
                    if(p==NULL){status = false;}
                    else{
                        p = p->next;
                        if((p==NULL)||(p->isi!="=")){status = false;}
                        else{
                            p = p->next;
                            if(p==NULL){status = false;}
                            else{
                                p = p->next;
                                if((p==NULL)||(p->isi!=";")){status = false;}
                            }
                        }
                    }
                }

            }
        }

    }

return status;
};
adrsyntax syntaxofdeletefrom(adrsyntax s, adrdb d){
    adrsyntax p,q=NULL; adrtable t; adrkolom k; adrisi i;
    p = s;
    if(is_deletefrom(s)==true){
        p = p->next->next;
        t = searchtable(d,p->isi);
        if(t==NULL){return NULL;}
        else{
            insertsyntax(&q,p->isi);
            p = p->next->next;
        k = searchkolom(t,p->isi);
        if(k==NULL){return NULL;}
        else{
            insertsyntax(&q,p->isi);
            p = p->next->next;
            i = searchisi(k,p->isi);
            if(i==NULL){return NULL;}
            else{
                insertsyntax(&q,p->isi);
                return q;
            }
        }

        }
    }
    else{return NULL;}

};
void executedeletesyntax(adrsyntax s, adrdb *d){
    adrsyntax p;
    p = s;
    deletefromrow(&(*d),p->isi,p->next->isi,p->next->next->isi);
};

bool is_truncatetable(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="truncate")){status = false;}
        else{
            p = p->next;
            if((p==NULL)||(p->isi!="table")){status = false;}
            else{
                p = p->next;
                if(p==NULL){status=false;}
                else{
                    p = p->next;
                    if((p==NULL)||(p->isi!=";")){status = false;}
                }
            }
        }

    return status;
}
adrsyntax syntaxoftruncate(adrsyntax s, adrdb d){
    adrsyntax p,q=NULL; adrtable t;
    p = s;
    if(is_truncatetable(s)==true){
        p = p->next->next;
        t = searchtable(d,p->isi);
        if(t==NULL){return NULL;}
        else{
            insertsyntax(&q,p->isi);
            return q;
        }
    }
    else{return NULL;}
};
void executetruncate(adrsyntax s, adrdb *d){
    adrsyntax p;
    p = s;
    truncatetable(d,p->isi);
};

bool is_drop(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="drop")){status = false;}
    else{
        p = p->next;
        if((p==NULL)||(p->isi!="table")){status = false;}
        else{
             p = p->next;
             if(p==NULL){status = false;}
             else{
                p = p->next;
                if((p==NULL)||(p->isi!=";")){status = false;}
             }
        }
    }
return status;
};
adrsyntax syntaxofdrop(adrsyntax s, adrdb d){
    adrsyntax p,q = NULL; adrtable t;
    p = s;
    if(is_drop(s)==true){
    t = searchtable(d,p->next->next->isi);
    if(t==NULL){cout<<"tabel tidak ada"<<endl; return NULL;}
    else{
        insertsyntax(&q,p->next->next->isi);
        return q;
    }
    }
    else{return NULL;}
};
void executedrop(adrsyntax s, adrdb *d){
    adrtable t;
    adrsyntax p;
    p = s;
    droptable(d,p->isi);
};

//---------------------------------------------------------------------------

//Desc syntax [S05]

bool is_desc(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="desc")){status = false;}
    else{
        p = p->next;
        if(p==NULL){status = false;}
        else{
            p = p->next;
            if((p==NULL)||(p->isi!=";")){status = false;}
        }
    }
    return status;
};
adrsyntax syntaxofdesc(adrsyntax s,adrdb d){
    adrsyntax p, q=NULL; adrtable t;
    p = s;
    if(is_desc(s)==true){
        p = p->next;
        t = searchtable(d,p->isi);
        if(t==NULL){cout<<"tabel tidak ada";return NULL;}
        else{
        insertsyntax(&q,p->isi);
        return q;}
    }
    else{return NULL;}
};
void executedesc(adrsyntax s, adrdb d){
    adrsyntax p;
    p = s;
    viewdesctable(d,p->isi);
};

//---------------------------------------------------------------------------

//update syntax [S06]
bool is_update(adrsyntax s){
    adrsyntax p; bool status = true;
    p = s;
    if((p==NULL)||(p->isi!="update")){status = false;}
    else{
        p = p->next;
        if(p==NULL){status = false;}
        else{
            p = p->next;
            if((p==NULL)||(p->isi!="set")){status = false;}
            else{
                p = p->next;
                if(p==NULL){status = false;}
                else{
                    p = p->next;
                    if((p==NULL)||(p->isi!="=")){status = false;}
                    else{
                        p = p->next;
                        if(p==NULL){status = false;}
                        else{
                            p = p->next;
                            if((p==NULL)||(p->isi!="where")){status = false;}
                            else{
                                p = p->next;
                                if(p==NULL){status = false;}
                                else{
                                    p = p->next;
                                    if((p==NULL)||(p->isi!="=")){status = false;}
                                    else{
                                        p = p->next;
                                        if(p==NULL){status=false;}
                                        else{
                                            p = p->next;
                                            if((p==NULL)||(p->isi!=";")){status = false;}
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

    }

    return status;
};
adrsyntax syntaxofupdate(adrsyntax s, adrdb d){
    adrsyntax p, q = NULL; adrtable t;adrkolom k;adrisi i;

    if(is_update(s)==true){
    p = s;
    p = p->next;
    t = searchtable(d,p->isi);
    if(t==NULL){cout<<"tabel tidak ada"<<endl;return NULL;}
    else{
        insertsyntax(&q,p->isi);
        p = p->next->next;
        k = searchkolom(t,p->isi);
        if(k==NULL){cout<< "invalid column"<<endl; return NULL;}
        else{
            insertsyntax(&q,p->isi);
            p = p->next->next;
            insertsyntax(&q,p->isi);
            p = p->next->next;
            k = searchkolom(t,p->isi);
            if(k==NULL){cout<< "invalid column"<<endl; return NULL;}
            else{
                insertsyntax(&q,p->isi);
                p = p->next->next;
                i = searchisi(k,p->isi);
                if(i==NULL){cout<< "no data found"<<endl;return NULL;}
                else{
                    insertsyntax(&q,p->isi);
                    return q;
                }

            }
        }

    }
}
else{return NULL;}
};
void executeupdate(adrsyntax s, adrdb d){
    adrsyntax p;
    p = s;
    updateisi(d,p->isi,p->next->isi,p->next->next->isi,p->next->next->next->isi,p->next->next->next->next->isi);
};


//---------------------------------------------------------------------------

void executor(adrdb *l, adrsyntax root, int *dec){
    adrsyntax p; string temp,tempkolom; adrtable t; adrkolom k; adrisi i; adrrow r;int rowno;
    p = root;
    if(p->isi=="create"){
        p = syntaxofcreate(root);
        if(p==NULL){cout<<"syntax salah"<<endl;}
        else{executecreate(p,l);cout<<endl<<"table created"<<endl;}
    }
    else if(p->isi=="drop"){
        p = syntaxofdrop(root,*l);
        if(p!=NULL){
            executedrop(p,l);
            cout<<endl<<"table dropped"<<endl;
        }
    }
    else if(p->isi=="insert"){
        p = syntaxofinsert(root,*l);
        if(p==NULL){cout<<"syntax salah"<<endl;}
        else{executeinsert(p,l);cout<<endl<<"values inserted"<<endl;}
    }
    else if(p->isi=="select"){
        p = syntaxofselectallnowherenosort(root,*l);
        if(p!=NULL){
                executeselectallnowherenosort(p,*l);
        }
        else{
            p = syntaxofselectallnowheresort(root,*l);
            if(p!=NULL){
                executeselectallnowheresort(p,*l);
        }
        }
    }
    else if(p->isi=="truncate"){
        p = syntaxoftruncate(root,*l);
        if(p!=NULL){
            executetruncate(p,l);
            cout<<endl<<"table cleaned"<<endl;
        }
    }
    else if(p->isi=="delete"){
        p = syntaxofdeletefrom(root,*l);
         if(p!=NULL){
            executedeletesyntax(p,l);
            cout<< endl<< "1 row deleted" << endl;
        }

    }
    else if(p->isi=="desc"){
        p = syntaxofdesc(root,*l);
        if(p!=NULL){
            executedesc(p,*l);
        }
    }
    else if(p->isi=="update"){
        p = syntaxofupdate(root,*l);
        if(p!=NULL){
            executeupdate(p,*l);
            cout<<endl << "1 row updated" << endl;
        }
    }
    else if(p->isi=="exit"){*dec = 1;}
    else{cout<< "syntax salah"<<endl;}
    emptysyntax(&root);

};
//------------------------------------------- menus and animation [008]



//-------------------------------------------  others [009]
