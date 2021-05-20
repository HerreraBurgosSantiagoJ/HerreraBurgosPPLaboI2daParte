/*
 * sBike.c
 *
 *  Created on: 20 may. 2021
 *      Author: plainsight
 */

#include <stdio_ext.h>
#include <stdlib.h>
#include "../Heathers/sBike.h"
#include "../Heathers/vallib.h"

int bike_init(sBike* list, int len )
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
}

int bike_add(sBike* list, int len, int id, char* brand, int wheelSize, char* color )
{
    int returnAux = -1;
    if( len > 0 && list != NULL )
    {
        for( int i = 0 ;i < len ;i++ )
        {
            if(list[i].isEmpty == 1)
            {
                list[i].id=id;
                val_strCpy(brand, list[i].brand, BRAND_LENGTH);
                list[i].wheelSize = wheelSize;
                val_strCpy(color, list[i].color, COLOR_LENGTH);
                list[i].isEmpty=0;
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

int bike_findById(sBike* list, int len,int id)
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

int bike_remove(sBike* list, int len, int id)
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

int bike_swap( sBike* bikeA, sBike* bikeB )
{
	int returnAux;
	sBike auxBike;
	if( bikeA != NULL && bikeB != NULL )
	{
		auxBike = *bikeA;
		*bikeA = *bikeB;
		*bikeB = auxBike;
		returnAux = 0;
	}
	return returnAux;
}

int bike_print(sBike bike)
{
	int returnAux = -1;
	if( bike.isEmpty == 0 )
	{
		printf("    %05d  |%25s  |%6d  |%15s\n",
		       bike.id, bike.brand, bike.wheelSize, bike.color);
		printf("-------------------------------------------------------------------------------------------\n");
	}
	return returnAux;
}

int bike_list(sBike* list, int bikesLength )
{
    int returnAux = -1;
    int flagFirstLoop = 1;
    for ( int i = 0 ; i < bikesLength; i++ )
    {
    	if( flagFirstLoop && list[i].isEmpty == 0 )
    	{
    		printf("\n     ID              Marca               Rodado         Color       \n");
    		printf("-------------------------------------------------------------------------------------------\n");
    		flagFirstLoop = 0;
    	}
        if ( list[i].isEmpty == 0 )
        {
        	bike_print(list[i]);
            returnAux = 0;
        }
    }
    return returnAux;
}

int bike_generateID(sBike* list, int len)
{
    int returnAux = -1;
    if( list != NULL && len > 0 )
    {
    	returnAux = 24;
    	for( int i = 0; i < len; i++ )
    	{
    		if( list[i].isEmpty == 0 && list[i].id > returnAux )
    		{
    			returnAux = list[i].id;
    		}
    	}
    	returnAux++;
    }
    return returnAux;
}

char bike_hasSpace(sBike* list, int len)
{
    char returnAux = -1;
    if( list != NULL && len > 0 )
    {
    	for( int i = 0; i < len; i++ )
    	{
    		if( list[i].isEmpty == 1 )
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    	if( returnAux == -1 )
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

int bike_isNotEmpty( sBike* list, int length )
{
	int returnAux = -1;
	if( list != NULL && length > 0 )
	{
		for( int i = 0; i < length; i++ )
		{
			if( list[i].isEmpty == 0 )
			{
				returnAux = 1;
				break;
			}
		}
		if( returnAux == -1 )
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

int bike_findEmpty( sBike* list, int length )
{
	int returnAux = -1;
	if( list != NULL && length > 0 )
	{
		for( int i = 0; i < length; i++ )
		{
			if( list[i].isEmpty == 1 )
			{
				returnAux = i;
				break;
			}
		}
	}
	return returnAux;
}

int bike_findGreaterID( sBike* list, int length )
{
	int returnAux = -1;
	int firstsWork = 1;
	if( list != NULL && length > 0 )
	{
		returnAux = 0;
		for( int i = 0; i < length; i++ )
		{
			if( ( firstsWork || returnAux < list[i].id ) &&
				list[i].isEmpty == 0 )
			{
				returnAux = list[i].id;
				firstsWork = 0;
			}
		}
	}
	return returnAux;
}

int bike_findMinorID( sBike* list, int length )
{
	int returnAux = -1;
	int firstsWork = 1;
	if( list != NULL && length > 0 )
	{
		for( int i = 0; i < length; i++ )
		{
			if( ( firstsWork || returnAux > list[i].id ) &&
				list[i].isEmpty == 0 )
			{
				returnAux = list[i].id;
				firstsWork = 0;
			}
		}
	}
	return returnAux;
}

int bike_hardcode( sBike* list, int len )
{
	int returnAux = -1;
	int auxId;
	if( list != NULL && len > 0 )
	{
		if( (auxId = bike_generateID(list, len)) == 0 && bike_add(list, len, auxId, "MarcaRandomA", 35, "ColorA") == 0 &&
			(auxId = bike_generateID(list, len)) == 0 && bike_add(list, len, auxId, "MarcaRandomB", 35, "ColorB") == 0 &&
			(auxId = bike_generateID(list, len)) == 0 && bike_add(list, len, auxId, "MarcaRandomC", 35, "ColorC") == 0 &&
			(auxId = bike_generateID(list, len)) == 0 && bike_add(list, len, auxId, "MarcaRandomD", 35, "ColorD") == 0 &&
			(auxId = bike_generateID(list, len)) == 0 && bike_add(list, len, auxId, "MarcaRandomE", 35, "ColorE") == 0 )
		{
			returnAux = 0;
		}
	}
	return returnAux;
}
