#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../Heathers/sServices.h"
#include "../Heathers/sWorks.h"
#include "../Heathers/sBike.h"
#include "../Heathers/vallib.h"

int work_init(sWork* list, int len )
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

int work_add(sWork* list, int len, int id, int idBike, int idService, sDate date)
{
    int returnAux = -1;
    if( len > 0 && list != NULL )
    {
        for( int i = 0 ;i < len ;i++ )
        {
            if(list[i].isEmpty == 1)
            {
                list[i].id=id;
                list[i].idBike=idBike;
                list[i].idService = idService;
                list[i].date = date;
                list[i].isEmpty=0;
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

int work_findById(sWork* list, int len,int id)
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

int work_remove(sWork* list, int len, int id)
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

int work_swap( sWork* workA, sWork* workB )
{
	int returnAux;
	sWork auxWork;
	if( workA != NULL && workB != NULL )
	{
		auxWork = *workA;
		*workA = *workB;
		*workB = auxWork;
		returnAux = 0;
	}
	return returnAux;
}

int work_sort(sWork* list, int len, int order, sBike* bikes, int bikesLen)
{
    int returnAux = -1;
    int bikePosition;
    int strCmpAux;
    if ( len > 0 && list != NULL )
    {
        for ( int i = 0; i < len; i++ )
        {
            for ( int j = i + 1; j < len; j++ )
            {
                if( ( list[i].date.year > list[j].date.year && order == 1 ) ||
                	( list[i].date.year < list[j].date.year && order == 0 ) )
                {
                	work_swap( &list[i], &list[j] );
                }
            }
        }
        for ( int i = 0; i < len; i++ )
        {
        	for ( int j = i + 1; j < len; j++ )
        	{
        		bikePosition = bike_findById(bikes, bikesLen, list[i].idBike);
        		strCmpAux = strncmp( bikes[bikePosition].brand, bikes[bikePosition+1].brand,
        							BRAND_LENGTH );
        		if( ( ( strCmpAux > 0 && order == 1 ) ||
        			( strCmpAux < 0 && order == 0 ) ) &&
        			list[i].date.year == list[j].date.year )
        		{
        			work_swap( &list[i], &list[j] );
        		}
        	}
        }
        returnAux = 0;
    }
    return returnAux;
}

int work_sortByBrand(sWork* list, int len, int order, sBike* bikes, int bikesLen)
{
    int returnAux = -1;
    int bikePosition;
    int strCmpAux;
    if ( len > 0 && list != NULL )
    {
        for ( int i = 0; i < len; i++ )
        {
        	for ( int j = i + 1; j < len; j++ )
        	{
        		bikePosition = bike_findById(bikes, bikesLen, list[i].idBike);
        		strCmpAux = strncmp( bikes[bikePosition].brand, bikes[bikePosition+1].brand,
        							BRAND_LENGTH );
        		if( ( strCmpAux > 0 && order == 1 ) ||
        			( strCmpAux < 0 && order == 0 ) )
        		{
        			work_swap( &list[i], &list[j] );
        		}
        	}
        }
        returnAux = 0;
    }
    return returnAux;
}

int work_list(sWork* list, int workLength, sBike* bikes, int bikesLen, sService* services, int servicesLength)
{
    int returnAux = -1;
    int flagFirstLoop = 1;
    int auxServId;
    int auxBikeId;
    for ( int i = 0 ; i < workLength; i++ )
    {
    	auxServId = serv_findByID(services, servicesLength, list[i].idService);
    	auxBikeId = bike_findById(bikes, bikesLen, list[i].idBike);
    	if( flagFirstLoop && list[i].isEmpty == 0 )
    	{
    		printf("\n     ID              Marca               Rodado         Servicio            Fecha       \n");
    		printf("-------------------------------------------------------------------------------------------\n");
    		flagFirstLoop = 0;
    	}
        if ( list[i].isEmpty == 0 )
        {
            printf("    %05d  |%25s  |%6d  |%15s  |%15s  |        %02d/%02d/%04d\n",
            		list[i].id, bikes[auxBikeId].brand, bikes[auxBikeId].wheelSize, bikes[auxBikeId].color, services[auxServId].description,
					list[i].date.day, list[i].date.month, list[i].date.year);
            printf("-------------------------------------------------------------------------------------------\n");
            returnAux = 0;
        }
    }
    return returnAux;
}

int work_generateID(sWork* list, int len)
{
    int returnAux = -1;
    if( list != NULL && len > 0 )
    {
    	returnAux = 0;
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

float work_totalGain(sWork* list, int workLen, sService* services, int servLen)
{
    float returnAux = -1;
    int flagFirstLoop = 1;
    int auxServID;
    if( list != NULL && workLen > 0 )
    {
    	returnAux = 0;
    	for ( int i = 0 ; i<workLen ; i++ )
    	{
    		if( flagFirstLoop && list[i].isEmpty == 0 )
    		{
    			auxServID = serv_findByID( services, servLen, list[i].idService);
    			returnAux += services[auxServID].price;
    			flagFirstLoop = 0;
    		}
    	}
    }
    return returnAux;
}

char work_hasSpace(sWork* list, int len)
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

int work_isNotEmpty( sWork* list, int length )
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

int work_findEmpty( sWork* list, int length )
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

int work_findGreaterID( sWork* list, int length )
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

int work_findMinorID( sWork* list, int length )
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
