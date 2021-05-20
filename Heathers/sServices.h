#ifndef SSERVICES_H_INCLUDED
#define SSERVICES_H_INCLUDED

#define DESCRIPTION_LENGTH 25

typedef struct{

 int id;
 char description[DESCRIPTION_LENGTH];
 float price;
 int isEmpty;

}sService;

#endif // SSERVICESS_H_INCLUDED

int serv_init(sService* list, int len);

int serv_add(sService* list, int len, int id, char* description, float price);

int serv_findByID(sService* list, int len, int id);

int serv_remove(sService* list, int len, int id);

int serv_list(sService* list, int length);

int serv_hardcode( sService* list, int len );


