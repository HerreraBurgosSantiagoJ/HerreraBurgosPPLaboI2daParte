#include "../Heathers/sServices.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../Heathers/vallib.h"

int serv_init(sService* list, int len)
{
    int returnAux = -1;
    if ( len > 0 && list != NULL )
    {
        for (int i = 0 ; i < len ; i++)
        {
            list[i].isEmpty = 1;
        }
        returnAux=0;
    }
    return returnAux;
}//good

int serv_add(sService* list, int len, int id, char* description, float price)
{
    int returnAux = -1;
    if( len > 0 && list != NULL )
    {
        for( int i = 0 ;i < len ;i++ )
        {
            if(list[i].isEmpty == 1)
            {
                list[i].id=id;
                val_strCpy(description, list[i].description, DESCRIPTION_LENGTH);
                list[i].price = price;
                list[i].isEmpty=0;
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

int serv_findByID(sService* list, int len, int id)
{
    int returnAux = -1;
    if ( len > 0 && list != NULL)
    {
        for ( int i = 0; i < len; i++ )
        {
            if ( list[i].id == id && list[i].isEmpty == 0 )
            {
                returnAux = i;
                break;
            }
        }
    }
    return returnAux;
}

int serv_remove(sService* list, int len, int id)
{
    int returnAux = -1;
    if ( len > 0 && list != NULL )
    {
        for ( int i = 0; i < len; i++ )
        {
            if ( list[i].id == id )
            {
                list[i].isEmpty = 1;
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

int serv_list(sService* list, int length)
{
    int returnAux = -1;
    int flagFirstLoop = 1;
    for ( int i = 0 ; i < length; i++ )
    {
    	if( flagFirstLoop && list[i].isEmpty == 0 )
    	{
    		printf("\n     ID           Description              Precio  \n");
    		printf("------------------------------------------------------\n");
    		flagFirstLoop = 0;
    	}
        if ( list[i].isEmpty == 0 )
        {
            printf("    %05d   |%15s  |%15.2f\n",
            		list[i].id, list[i].description, list[i].price);
            printf("------------------------------------------------------\n");
            returnAux = 0;
        }
    }
    return returnAux;
}

int serv_hardcode( sService* list, int len )
{
	int returnAux = -1;
	char desc[4][10] = {"Limpieza", "Parche", "Centrado", "Cadena"};
	float prices[4] = {250, 300, 400, 350};
	if( list != NULL && len == 4 )
	{
		for( int i = 0; i < len; i++ )
		{
			list[i].id = 20000 + i;
			val_strCpy( desc[i], list[i].description, DESCRIPTION_LENGTH);
			list[i].price = prices[i];
			list[i].isEmpty = 0;
		}
		returnAux = 0;
	}
	return returnAux;
}
