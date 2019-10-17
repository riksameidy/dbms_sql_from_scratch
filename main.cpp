#include "header.cpp"

/*
Authors:    - Riksa Meidy Karim (1301142289)
            - Amalya Citra Pradana (1301140389)
            - Anita Auliani (1301144349)

Description: Program yang mensimulasikan sebuah DBMS
*/

int main()
{
    string temp; adrsyntax syn=NULL; int dec=0;
    llist a;adruser user=NULL; adrdb d=NULL; adrtable t = NULL; adrkolom k=NULL; adrisi i=NULL;
    a.first = NULL;
    insertuser(&a,"Riksa","1301142289");
    insertdb(a.first,"my DB");
    while (dec!=1){
    syn = selector();
    executor(&(a.first->data),syn, &dec);
    syn = NULL;
    }

    return 0;
}
