/*
 * aux_main.h
 *
 *  Created on: 24 mar. 2021
 *      Author: plainsight
 */

#ifndef HEATHERS_AUX_MAIN_H_
#define HEATHERS_AUX_MAIN_H_

#include "sServices.h"
#include "sBike.h"
#include "sWorks.h"

typedef struct{
	int id;
	int content;
}sAuxInt;

#endif /* HEATHERS_AUX_MAIN_H_ */

//Program Title
#define TITLE "ABM"
#define SUB_TITLE_MAIN "Menu Principal"
#define SUB_TITLE_REG "ALTAS"
#define SUB_TITLE_MOD "MODIFICAR"
#define SUB_TITLE_DEL "BAJAS"
#define SUB_TITLE_LIST_WORKS "LISTA DE TRABAJOS"
#define SUB_TITLE_LIST_WORKS_BRAND "LISTA DE TRABAJOS POR MARCA"
#define SUB_TITLE_LIST_SERV "LISTA DE SERVICIOS"
#define SUB_TITLE_INFORM_SERV_DEMAND "INFORME DE DEMANDA DE SERVICIOS"
#define SUB_TITLE_ERROR "Error"

//Output Menu(Main)
#define MENU_MAIN_ONE "\nA. ALTA TRABAJO."
#define MENU_MAIN_TWO "\nB. MODIFICACAR TRABAJO."
#define MENU_MAIN_THREE "\nC. BAJA TRABAJO."
#define MENU_MAIN_FOUR "\nD. LISTAR TRABAJOS."
#define MENU_MAIN_FIVE "\nE. LISTAR SERVICIOS."
#define MENU_MAIN_SIX "\nF. LISTAR TRABAJOS POR MARCA."
#define MENU_MAIN_SEVEN "\nG. INFORME DE DEMANDA DE SERVICIOS."
#define MENU_MAIN_EIGTH "\nH. Salir."

//Outut Modify Menu
#define MENU_MOD_ONE "\n1. Cambiar Marca."
#define MENU_MOD_TWO "\n2. Cambiar Servicio."
#define MENU_MOD_THREE "\n3. Modificar otro Trabajo."
#define MENU_MOD_FOUR "\n4. Volver al Menu Principal"

//Output
#define TXT_FULL_DATABASE "\nNo es posible, base de datos llena."
#define TXT_EMPTY_DATABASE "\nNo es posible, base de datos vacia."
#define TXT_NEW_ID "\nEl ID del nuevo trabajo es %d. El ID de la nueva bicicleta es %d."
#define TXT_WORK_DATA "\nID: %05d\nMarca: %s\nRodado: %d\nColor: %s\nServicio: %s\nFecha: %02d/%02d/%04d"
#define TXT_INFORM_SERV_DEMAND "\n1. %s: %d Pedidos\n2. %s: %d Pedidos\n3. %s: %d Pedidos\n4. %s: %d Pedidos"
#define TXT_REMOVAL_SUCCESES "\nTrabajo dado de BAJA correctamente."
#define GOODBYE "\nHasta Luego! :D\n"

//Output Errors
#define MAIN_ERROR_MALFUNCTION_EXIT "\nEl programa parece estar funcionando mal, este se cerrará."
#define MAIN_ERROR_MISUSE_EXIT "\nEl usuario no es apto para el uso del programa, este se cerrará"

//Input options
#define INP_TXT_OPTION "\nOpción: "

#define INP_TXT_DATA_OK "\nSon estos datos correctos? (Si=1/No=0): "
#define INP_TXT_MORE_REG "\nDesea dar de ALTA a otro trabajo? (Si=1/No=0): "
#define INP_TXT_MORE_DEL "\nDesea dar de BAJA a otro trabajo? (Si=1/No=0): "

#define INP_TXT_DEL_ID "\nIngrese el ID del trabajo( Para cancelar ingrese 0 ): "

//Input employee data
#define INP_TXT_BRAND "\nIngrese la marca de la bicicleta: "
#define INP_TXT_COLOR "\nIngrese la marca de la bicicleta: "
#define INP_TXT_WHEEL_SIZE "\nIngrese el rodado: "
#define INP_TXT_SERVICE_ID "\nIngrese el ID de servicio: "
#define INP_TXT_DATE "\nIngrese la fecha (Formato dd/mm/aaaa apartir del 2020): "

//Input errors
#define INP_ERROR_MAIN_OPTION "\nError! Lo ingresado no corresponde con ninguna de las opciones del menu principal.\nIntentos Restantes: %d"
#define INP_ERROR_MOD_OPTION "\nError! Lo ingresado no corresponde con ninguna de las opciones de este menu.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_EXPECTED_INT "\nError! El numero ingresado no corresponde con los valores esperados.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_NUMBER "\nError! Lo ingresado no es un numero.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_BRAND "\nError! Lo ingresado contiene caracteres no esperados en una marca.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_COLOR "\nError! Lo ingresado contiene caracteres no esperados en un color.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_SECTOR "\nError! Lo ingresado contiene caracteres no esperados en una marca.\nIntentos Restantes: %d"
#define INP_ERROR_NOT_DATE "\nError! Lo ingresado no es un numero.\nIntentos Restantes: %d"

//Numerical constants
#define MAX_WORKS 24
#define MAX_SERVICES 4
#define MAX_SERVICES_ID 20003
#define MIN_SERVICES_ID 20000
#define MAX_TRYS 3
#define LEN_MAIN_OPT 9
#define LEN_MODY_OPT 4
#define LEN_INT_YN_OPT 2

int main_registerWork( sWork* works, int worksLength, sBike* bikes, int bikesLen,sService* services, int servicesLen );
int main_deleteWork( sWork* works, int length, sBike* bikes, int bikesLen, sService* services, int servicesLen );
void mody_menuShow( void );
int mody_menu( sWork* work, int* keepOn, sBike* bikes, int bikesLen, sService* services, int servicesLen );
int main_modifyWork( sWork* works, int length, sBike* bikes, int bikesLen, sService* services, int servicesLen );
int main_listWorks( sWork* works, int worksLen, sBike* bikes, int bikesLen, sService* services, int servicesLen );
int main_listServices( sService* services, int servicesLen );
int main_listWorksByBrand( sWork* works, int worksLen, sBike* bikes, int bikesLen, sService* services, int servicesLen );
void main_menuShow( void );
int main_menu( sWork* works, int worksLength, sBike* bikes, int bikesLen, sService* services, int servLength );
