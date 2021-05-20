/*
 * sBike.h
 *
 *  Created on: 20 may. 2021
 *      Author: plainsight
 */

#ifndef HEATHERS_SBIKE_H_
#define HEATHERS_SBIKE_H_

#define BRAND_LENGTH 25
#define COLOR_LENGTH 15

typedef struct{

	int id;
	char brand[BRAND_LENGTH];
	int wheelSize;
	char color[COLOR_LENGTH];
	int isEmpty;

}sBike;

#endif /* HEATHERS_SBIKE_H_ */

int bike_init(sBike* list, int len );

int bike_add(sBike* list, int len, int id, char* brand, int wheelSize, char* color );

int bike_findById(sBike* list, int len,int id);

int bike_remove(sBike* list, int len, int id);

int bike_swap( sBike* bikeA, sBike* bikeB);

int bike_print(sBike bike);

int bike_list(sBike* list, int bikesLength );

int bike_generateID(sBike* list, int len);

char bike_hasSpace(sBike* list, int len);

int bike_isNotEmpty( sBike* list, int length );

int bike_findEmpty( sBike* list, int length );

int bike_findGreaterID( sBike* list, int length );

int bike_findMinorID( sBike* list, int length );

int bike_hardcode( sBike* list, int len );
