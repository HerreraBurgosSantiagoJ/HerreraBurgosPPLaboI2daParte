/*
 * aux_main.c
 *
 *  Created on: 13 may. 2021
 *      Author: plainsight
 */
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "../Heathers/aux_main.h"
#include "../Heathers/steart.h"
#include "../Heathers/input_lib.h"
#include "../Heathers/my_system.h"
#include "../Heathers/sServices.h"
#include "../Heathers/sWorks.h"
//#include "../Heathers/"

int main_registerWork( sWork* works, int worksLength, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	int allOk = 1;
	int options[LEN_INT_YN_OPT] = {0,1};
	int keepOn;
	int auxServiceId;
	sWork auxWork;
	sBike auxBike;
	if( works != NULL && worksLength > 0 )
	{
		do
		{
			progHeader(TITLE);
			subHeader( SUB_TITLE_REG );
			keepOn = 0;
			if( allOk && work_hasSpace(works, worksLength) &&
				bike_hasSpace(bikes, bikesLen) )
			{
				auxWork.id = work_generateID( works, worksLength);
				auxBike.id = bike_generateID(bikes, bikesLen);
				auxWork.idBike = auxBike.id;
				auxWork.isEmpty = 0;
				auxBike.isEmpty = 0;
				printf( TXT_NEW_ID, auxWork.id, auxWork.idBike );
			}
			else if( allOk )
			{
				printf( TXT_FULL_DATABASE );
				returnAux = 0;
				sys_pause();
				break;
			}

			if( inp_getName( auxBike.brand, INP_TXT_BRAND, BRAND_LENGTH,
							MAX_TRYS, INP_ERROR_NOT_BRAND)== 0 &&
				inp_getInt(&auxBike.wheelSize, INP_TXT_WHEEL_SIZE, MAX_TRYS, INP_ERROR_NOT_NUMBER ) == 0 &&
				inp_getName( auxBike.color, INP_TXT_COLOR, COLOR_LENGTH,
											MAX_TRYS, INP_ERROR_NOT_COLOR)== 0 &&
				serv_list(services, servicesLen) == 0 &&
				inp_getIntRange(&auxWork.idService, INP_TXT_SERVICE_ID, MAX_TRYS, MIN_SERVICES_ID, MAX_SERVICES_ID, INP_ERROR_NOT_EXPECTED_INT, INP_ERROR_NOT_NUMBER)== 0 &&
				inp_getDate( &auxWork.date, INP_TXT_DATE, MAX_TRYS, 2020, INP_ERROR_NOT_NUMBER, INP_ERROR_NOT_DATE) == 0 )
			{
				auxServiceId = serv_findByID(services, servicesLen, auxWork.idService);
				printf( TXT_WORK_DATA, auxWork.id, auxBike.brand, auxBike.wheelSize, auxBike.color, services[auxServiceId].description , auxWork.date.day, auxWork.date.month, auxWork.date.year );
				returnAux = inp_getIntConcrete( &allOk, INP_TXT_DATA_OK,
												MAX_TRYS, LEN_INT_YN_OPT,
												options,
												INP_ERROR_NOT_EXPECTED_INT,
												INP_ERROR_NOT_NUMBER );
			}
			else
			{
				returnAux = -2;
				break;
			}

			if( allOk && returnAux == 0 &&
				work_add(works, worksLength, auxWork.id, auxWork.idBike, auxWork.idService, auxWork.date) == 0 &&
				bike_add(bikes, bikesLen, auxBike.id, auxBike.brand, auxBike.wheelSize, auxBike.color) == 0)
			{
				returnAux = inp_getIntConcrete( &keepOn, INP_TXT_MORE_REG,
												MAX_TRYS, LEN_INT_YN_OPT,
												options,
												INP_ERROR_NOT_EXPECTED_INT,
												INP_ERROR_NOT_NUMBER );
			}
			else if( returnAux == 0 )
			{
				keepOn = 1;
			}


		}while( keepOn && returnAux != -2 );
	}
	return returnAux;
}

int main_deleteWork( sWork* works, int length, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	int options[LEN_INT_YN_OPT] = {0,1};
	int auxID;
	int auxService;
	int auxBike;
	int auxMax;
	int keepOn;
	int position;
	int allOk = 1;
	int trys = MAX_TRYS;
	if( works != NULL && length > 0 )
	{
		do
		{
			keepOn = 0;
			progHeader( TITLE );
			subHeader( SUB_TITLE_DEL );

			if( work_isNotEmpty( works, length ) )
			{
				work_list(works, length, bikes, bikesLen, services, servicesLen);
			}
			else
			{
				printf( TXT_EMPTY_DATABASE );
				sys_pause();
				returnAux = 0;
				break;
			}

			auxMax = work_findGreaterID(works, length);

			if( inp_getIntRange( &auxID, INP_TXT_DEL_ID, trys, 0, auxMax,
								INP_ERROR_NOT_EXPECTED_INT,
								INP_ERROR_NOT_NUMBER) == 0
				&& auxID != 0
				&& (position = work_findById(works, length, auxID)) != -1 )
			{
				auxService = serv_findByID(services, servicesLen, works[position].idService);
				auxBike = bike_findById(bikes, bikesLen, works[position].idBike);
				progHeader( TITLE );
				subHeader( SUB_TITLE_DEL );
				printf( TXT_WORK_DATA, works[position].id,
						bikes[auxBike].brand, bikes[auxBike].wheelSize, bikes[auxBike].color,
						services[auxService].description,
						works[position].date.day, works[position].date.month,
						works[position].date.year );
				returnAux = inp_getIntConcrete(&allOk, INP_TXT_DATA_OK,
												MAX_TRYS, LEN_INT_YN_OPT,
												options,
												INP_ERROR_NOT_EXPECTED_INT,
												INP_ERROR_NOT_NUMBER);
			}
			else if( auxID == 0 )
			{
				returnAux = 0;
				break;
			}
			else if( position == -1 && trys > 0 )
			{
				trys--;
				printf( INP_ERROR_NOT_EXPECTED_INT, trys );
				sys_pause();
				keepOn = 1;
				continue;
			}
			else if( position == -1 )
			{
				returnAux = -2;
				break;
			}

			if( allOk )
			{
				returnAux = work_remove(works, length, auxID);
				printf( TXT_REMOVAL_SUCCESES );
			}
			else
			{
				keepOn = 1;
				continue;
			}

			returnAux = inp_getIntConcrete( &keepOn, INP_TXT_MORE_DEL, MAX_TRYS,
											LEN_INT_YN_OPT, options,
											INP_ERROR_NOT_EXPECTED_INT,
											INP_ERROR_NOT_NUMBER );

		}while( keepOn && returnAux == 0 );
	}
	return returnAux;
}

void mody_menuShow( void )
{
	printf( MENU_MOD_ONE );
	printf( MENU_MOD_TWO );
	printf( MENU_MOD_THREE );
	printf( MENU_MOD_FOUR );
}

int mody_menu( sWork* work, int* keepOn, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	int options[LEN_MODY_OPT] = {1, 2, 3, 4};
	int option = 0;
	int auxService;
	int auxBike;
	if( work != NULL )
	{
		do
		{
			progHeader(TITLE);
			subHeader(SUB_TITLE_MOD);
			auxService = serv_findByID(services, servicesLen, work->idService);
			auxBike = bike_findById(bikes, bikesLen, work->idBike);
			printf( TXT_WORK_DATA, work->id, bikes[auxBike].brand,
					bikes[auxBike].wheelSize, bikes[auxBike].color,
					services[auxService].description,
					work->date.day, work->date.month,
					work->date.year );
			mody_menuShow();
			if( inp_getIntConcrete(&option, INP_TXT_OPTION, MAX_TRYS,
											LEN_MODY_OPT, options,
											INP_ERROR_MOD_OPTION,
											INP_ERROR_NOT_NUMBER) != 0 )
			{
				returnAux = -2;
				break;
			}
			switch ( option )
			{
			case 1:
				returnAux = inp_getName( bikes[auxBike].brand, INP_TXT_BRAND, BRAND_LENGTH, MAX_TRYS, INP_ERROR_NOT_BRAND);
				break;
			case 2:
				serv_list(services, servicesLen);
				returnAux = inp_getIntRange(&work->idService, INP_TXT_SERVICE_ID, MAX_TRYS, MIN_SERVICES_ID, MAX_SERVICES_ID, INP_ERROR_NOT_EXPECTED_INT, INP_ERROR_NOT_NUMBER);
				break;
			case 3:
				*keepOn = 1;
				returnAux = 0;
				break;
			case 4:
				returnAux = 0;
				break;
			}
		}while( returnAux != -2 && option != 3 && option != 4 );
	}
	return returnAux;
}

int main_modifyWork( sWork* works, int length, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	int keepOn;
	int auxMax;
	int auxID;
	int position;
	if( works != NULL && length > 0 )
	{
		do
		{
			keepOn = 0;
			progHeader( TITLE );
			subHeader( SUB_TITLE_MOD );

			if( work_isNotEmpty(works, length) )
			{
				work_list(works, length, bikes, bikesLen, services, servicesLen);
			}
			else
			{
				printf( TXT_EMPTY_DATABASE );
				sys_pause();
				returnAux = 0;
				break;
			}

			auxMax = work_findGreaterID(works, length);

			if( inp_getIntRange( &auxID, INP_TXT_DEL_ID, MAX_TRYS, 0,
								auxMax, INP_ERROR_NOT_EXPECTED_INT,
								INP_ERROR_NOT_NUMBER) == 0 &&
				auxID != 0)
			{
				position = work_findById(works, length, auxID);
				returnAux = mody_menu( &works[position], &keepOn, bikes, bikesLen, services, servicesLen);
			}
			else if( auxID == 0 )
			{
				returnAux = 0;
			}
			else
			{
				returnAux = -2;
			}

		}while( keepOn && returnAux == 0 );
	}
	return returnAux;
}

int main_listWorks( sWork* works, int worksLen, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	if( works != NULL &&
		services != NULL &&
		worksLen > 0 &&
		servicesLen > 0 )
	{
		progHeader(TITLE);
		subHeader(SUB_TITLE_LIST_WORKS);
		if( work_sort(works, worksLen, 1, bikes, bikesLen) == 0 )
		{
			returnAux = work_list(works, worksLen, bikes, bikesLen, services, servicesLen);
		}
	}
	return returnAux;
}

int main_listServices( sService* services, int servicesLen )
{
	int returnAux = -1;
	if( services != NULL && servicesLen > 0 )
	{
		progHeader(TITLE);
		subHeader(SUB_TITLE_LIST_SERV);
		returnAux = serv_list(services, servicesLen);
	}
	return returnAux;
}

int main_listWorksByBrand( sWork* works, int worksLen, sBike* bikes, int bikesLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	if( works != NULL && bikes != NULL && services != NULL &&
		worksLen > 0 && bikesLen > 0 && servicesLen > 0 )
	{
		progHeader(TITLE);
		subHeader(SUB_TITLE_LIST_WORKS_BRAND);
		if( work_sortByBrand(works, worksLen, 1, bikes, bikesLen) == 0 )
		{
			returnAux = work_list(works, worksLen, bikes, bikesLen, services, servicesLen);
		}
	}
	return returnAux;
}

static int main_auxSort( sAuxInt* list, int len, int order)
{
	int returnAux = -1;
	sAuxInt auxStr;
	if( list != NULL && len > 0 && ( order == 0 || order == 1 ) )
	{
		for(int i = 0; i < len; i++)
		{
			for(int j = i + 1; j < len; i++)
			{
				if( ( list[i].content < list[j].content && order == 0 )||
					( list[i].content > list[j].content && order == 1 ) )
				{
					auxStr = list[i];
					list[i] = list[j];
					list[j] = auxStr;
				}
			}
		}
		returnAux = 0;
	}
	return returnAux;
}

int main_informServDemand( sWork* works, int worksLen, sService* services, int servicesLen )
{
	int returnAux = -1;
	int auxServiceA;
	int auxServiceB;
	int auxServiceC;
	int auxServiceD;
	sAuxInt order[4] = { {20000,0},
						 {20001,0},
						 {20002,0},
						 {20003,0}};
	if( works != NULL && services != NULL &&
		worksLen > 0 && servicesLen > 0 )
	{
		for( int i = 0; i < worksLen; i++)
		{
			switch( works[i].idService )
			{
			case 20000:
				order[0].content++;
				break;
			case 20001:
				order[1].content++;
				break;
			case 20002:
				order[2].content++;
				break;
			case 20003:
				order[3].content++;
				break;
			}
		}
		if( main_auxSort( order, 4, 0) == 0 &&
			(auxServiceA = serv_findByID(services, servicesLen, order[0].id)) == 0 &&
			(auxServiceB = serv_findByID(services, servicesLen, order[1].id)) == 0 &&
			(auxServiceC = serv_findByID(services, servicesLen, order[2].id)) == 0 &&
			(auxServiceD = serv_findByID(services, servicesLen, order[3].id)) == 0)
		{
			progHeader(TITLE);
			subHeader(SUB_TITLE_INFORM_SERV_DEMAND);
			printf( TXT_INFORM_SERV_DEMAND, services[auxServiceA].description, order[0].content, services[auxServiceB].description, order[1].content, services[auxServiceC].description, order[2].content, services[auxServiceD].description, order[3].content);
			returnAux = 0;
		}
	}
	return returnAux;
}

int main_redBikes( sWork* works, int worksLen, sBike* bikes, int bikesLen )
{
	int returnAux = -1;
	int auxBikes = 0;
	int redBikes = 0;
	if( works != NULL && bikes != NULL && worksLen > 0 && bikesLen > 0 )
	{
		for( int i = 0; i < worksLen; i++ )
		{
			auxBikes = bike_findById(bikes, bikesLen, works[i].idBike);
			if( strcmp(bikes[auxBikes].color,"Rojo\n") == 0 )
			{
				redBikes++;
			}
		}
		progHeader(TITLE);
		subHeader(SUB_TITLE_BICICLETAS_ROJAS);
		printf(TXT_RED_BIKES, redBikes);
		returnAux = 0;
	}
	return returnAux;
}

void main_menuShow( void )
{
	printf( MENU_MAIN_ONE );
	printf( MENU_MAIN_TWO );
	printf( MENU_MAIN_THREE );
	printf( MENU_MAIN_FOUR );
	printf( MENU_MAIN_FIVE );
	printf( MENU_MAIN_SIX );
	printf( MENU_MAIN_SEVEN );
	printf( MENU_MAIN_EIGTH );
}

int main_menu( sWork* works, int worksLength, sBike* bikes, int bikesLen, sService* services, int servLength )
{
	int returnAux = -1;
	char option = ' ';
	char options[LEN_MAIN_OPT] = "ABCDEFGHI\n";
	if( works != NULL && worksLength > 0 )
	{
		do
		{
			progHeader( TITLE );
			subHeader( SUB_TITLE_MAIN );
			main_menuShow();
			returnAux = inp_getCharConcrete( &option, INP_TXT_OPTION, MAX_TRYS, LEN_MAIN_OPT, options, INP_ERROR_MAIN_OPTION);
			if( returnAux == -2 )
			{
				break;
			}
			switch(option)
			{
			case 'A':
				if( work_hasSpace( works, worksLength ) )
				{
					returnAux = main_registerWork(works, worksLength, bikes, bikesLen, services, servLength);
				}
				else
				{
					printf( TXT_FULL_DATABASE );
					sys_pause();
				}
				break;
			case 'B':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_modifyWork(works, worksLength, bikes, bikesLen, services, servLength);
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'C':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_deleteWork(works, worksLength, bikes, bikesLen, services, servLength);
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'D':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_listWorks(works, worksLength, bikes, bikesLen, services, servLength);
					sys_pause();
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'E':
				returnAux = main_listServices(services, servLength);
				sys_pause();
				break;
			case 'F':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_listWorksByBrand(works, worksLength, bikes, bikesLen, services, servLength);
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'G':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_informServDemand(works, worksLength, services, servLength);
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'H':
				if( work_isNotEmpty(works, worksLength) == 1 )
				{
					returnAux = main_redBikes(works, worksLength, bikes, bikesLen);
				}
				else
				{
					printf( TXT_EMPTY_DATABASE );
					sys_pause();
				}
				break;
			case 'I':
				printf( GOODBYE );
				returnAux = 0;
				break;
			}
		}while( option != 'I' && returnAux == 0 );
	}
	return returnAux;
}
