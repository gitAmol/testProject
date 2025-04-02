#include <stdio.h>

typedef struct
{
	char acString[100];
	char cStrLen;

}STRING_STRUCT;

void swap( STRING_STRUCT *pstSrc, STRING_STRUCT *pstDest )
{
	STRING_STRUCT stTemp = { 0, };

	memcpy( &stTemp,  pstSrc, sizeof ( STRING_STRUCT ));

	memcpy( pstSrc,  pstDest, sizeof ( STRING_STRUCT ));

	memcpy( pstDest, &stTemp, sizeof ( STRING_STRUCT ));
}

unsigned char strings_sort(  STRING_STRUCT *pstStringArray, unsigned char ucSize )
{
	unsigned char ucPivot = 0;
	unsigned char uBigIndex  = 0;
	unsigned char uSmallIndex  = ucSize - 1;
	int			  nCmpResult = 0;
	if ( ucSize == 0 )
	{
		return 0;
	}

	ucPivot = uBigIndex;

	while( uBigIndex < uSmallIndex )
	{
		while( ( ( nCmpResult = strcmp( pstStringArray[ ucPivot ].acString, pstStringArray[ uBigIndex ].acString )) >= 0 ) \
					&& ( uBigIndex < uSmallIndex ))
		{
			uBigIndex++;
		}

		while( ( nCmpResult = strcmp( pstStringArray[ ucPivot ].acString, pstStringArray[ uSmallIndex ].acString )) < 0 )
		{
			uSmallIndex--;
		}

		if( uBigIndex < uSmallIndex )
		{
			swap( &pstStringArray[ uBigIndex ], &pstStringArray[ uSmallIndex ] );
		}
	}

	swap( &pstStringArray[ ucPivot ], &pstStringArray[ uSmallIndex ] );

	strings_sort( &pstStringArray[0], ucSize/2 );

	strings_sort( &pstStringArray[ucPivot + 1], ( ucSize-ucPivot-1) );

	return 0;
}

unsigned char sort_a_string( char *pstString, unsigned char nStringLength )
{

	unsigned char ucPivot = 0;
	unsigned char uBigIndex  = 0;
	unsigned char uSmallIndex  = nStringLength - 1;
	int			  nCmpResult = 0;

	if ( nStringLength == 0 )
	{
		return 0;
	}

	ucPivot = uBigIndex;

	while( uBigIndex < uSmallIndex )
	{
		while(  ( pstString[ uBigIndex ] <= pstString[ ucPivot ] ) && ( uBigIndex < uSmallIndex ) )
		{
			uBigIndex++;
		}

		while(  pstString[ uSmallIndex ] > pstString[ ucPivot ] )
		{
			uSmallIndex--;
		}

		if( uBigIndex < uSmallIndex )
		{
			char cTemp = 0;
			cTemp = pstString[ uBigIndex ];
			pstString[ uBigIndex ] = pstString[ uSmallIndex ];
			pstString[ uSmallIndex ] = cTemp;
		}
	}

	{
			char cTemp = 0;
			cTemp = pstString[ ucPivot ];
			pstString[ ucPivot ] = pstString[ uSmallIndex ];
			pstString[ uSmallIndex ] = cTemp;
	}

	sort_a_string( &pstString[0], nStringLength/2 );

	sort_a_string( &pstString[nStringLength + 1], ( nStringLength-ucPivot-1) );

	return 0;
}

unsigned char sort_Integer( int *pstIntArray, unsigned int nStringLength )
{

	unsigned char ucPivot = 0;
	unsigned char uBigIndex  = 0;
	unsigned char uSmallIndex  = nStringLength - 1;
	int			  nCmpResult = 0;

	if ( nStringLength == 0 )
	{
		return 0;
	}

	ucPivot = uBigIndex;

	while( uBigIndex < uSmallIndex )
	{
		while(  ( pstIntArray[ uBigIndex ] <= pstIntArray[ ucPivot ] ) && ( uBigIndex < uSmallIndex ) )
		{
			uBigIndex++;
		}

		while(  pstIntArray[ uSmallIndex ] > pstIntArray[ ucPivot ] )
		{
			uSmallIndex--;
		}

		if( uBigIndex < uSmallIndex )
		{
			int nTemp = 0;
			nTemp = pstIntArray[ uBigIndex ];
			pstIntArray[ uBigIndex ] = pstIntArray[ uSmallIndex ];
			pstIntArray[ uSmallIndex ] = nTemp;
		}
	}

	{
			int nTemp = 0;
			nTemp = pstIntArray[ ucPivot ];
			pstIntArray[ ucPivot ] = pstIntArray[ uSmallIndex ];
			pstIntArray[ uSmallIndex ] = nTemp;
	}

	sort_a_string( &pstIntArray[0], nStringLength/2 );

	sort_a_string( &pstIntArray[nStringLength + 1], ( nStringLength-ucPivot-1) );

	return 0;
}


int calculateNumberofLines( STRING_STRUCT *pstStringArray, unsigned char ucNumOfString, unsigned int nScreenWidth )
{
	unsigned int unTotalChar = 0;
	unsigned char ucCount = 0;
	float		  fLines = 0;
	for( ucCount = 0; ucCount < ucNumOfString; ++ucCount )
	{
		unTotalChar += pstStringArray[ ucCount ].cStrLen;
	}

	unTotalChar += ucNumOfString * 2;

	if( unTotalChar >  nScreenWidth )
	{
		fLines = ( (float ) unTotalChar) / nScreenWidth;
	}
	else
	{
		fLines = ( (float ) nScreenWidth)/unTotalChar;
	}

	return fLines + 0.9;
}

int arrangeString( STRING_STRUCT *pstStringArray, unsigned char ucNumOfString, unsigned int nScreenWidth, unsigned int unNumOfLines )
{
	char *pcStringToDisplay = NULL;
	int   stringcount = 0;
	int   lineCount = 0;
	unsigned int   *pnStringLength = NULL;
	char *pcPosition = NULL;
	char cStringLen = 0;

	pcStringToDisplay = (char*) malloc( nScreenWidth * unNumOfLines * sizeof(char) +  unNumOfLines );

	pnStringLength    = (int *) malloc( sizeof(char) + unNumOfLines );

	memset( pcStringToDisplay, '\0', ( nScreenWidth * unNumOfLines * sizeof(char) +  unNumOfLines ) );

	while( stringcount <  ucNumOfString )
	{
		lineCount = 0;

		while( ( lineCount <  unNumOfLines ) )
		{
			if( stringcount >=  ucNumOfString )
				break;

			pcPosition =  pcStringToDisplay + lineCount * nScreenWidth * sizeof( char ) + 1;

			cStringLen = strlen( pcPosition );

			strcpy( &pcPosition[ cStringLen ], pstStringArray[ stringcount ].acString );

			strcpy( &pcPosition[ strlen( pcPosition )], "__" );

			++lineCount;

			stringcount++;
		}

		lineCount = 0;

		while( lineCount < unNumOfLines )
		{
			pcPosition =  pcStringToDisplay + lineCount * nScreenWidth * sizeof( char ) + 1;

			pnStringLength[lineCount] = strlen( pcPosition );

			lineCount++;
		}

		sort_Integer( pnStringLength, lineCount );

		lineCount = 0;

		while( ( lineCount <  unNumOfLines ) )
		{
			int i = 0;
			int lenghth = 0;
			pcPosition =  pcStringToDisplay + lineCount * nScreenWidth * sizeof( char ) + 1;
			{
				lenghth = ( pnStringLength[ unNumOfLines -1 ] - strlen( pcPosition ));
				if( lenghth < nScreenWidth )
				{
					for( i = 0; i < lenghth; ++i )
					{
						strcpy( &pcPosition[ strlen( pcPosition )], "_" );
					}
				}
			}

			lineCount++;
		}


	}

	lineCount = 0;
	while( lineCount <  unNumOfLines )
	{
		pcPosition =  pcStringToDisplay + lineCount * nScreenWidth * sizeof( char ) + 1;
		printf( "%s\n", pcPosition );
		lineCount++;
	}

	free( pcStringToDisplay );

}


#define FILENAME D-small

int main ()
{
	STRING_STRUCT StringStruct[100] = { 0, };
	int i = 0;
    int NumberOfStrings = 0;
    int WindowWidth = 0;

    FILE     *pFileInputPointer  = NULL;

    pFileInputPointer = fopen("D-small.in","r");

    if ( NULL == pFileInputPointer )
    {
        printf("\nError Reading File \n");
        return -1;
    }

    if( !(fscanf( pFileInputPointer,"%d %d", &WindowWidth, &NumberOfStrings ) == 1 ) )
    {
        return -1;
    }

    printf("______%d,%d___________\n",WindowWidth, NumberOfStrings);

	for(i = 0; i < NumberOfStrings; i ++ )
	{
		fscanf( pFileInputPointer, "%s", StringStruct[i].acString );

		StringStruct[i].cStrLen = strlen( StringStruct[i].acString );

		sort_a_string( StringStruct[i].acString, StringStruct[i].cStrLen );
	}

	strings_sort( StringStruct, NumberOfStrings );


	printf("sorted data is:\n");
	for(i = 0; i < NumberOfStrings; ++i )
	{
		printf("String:[%s] StrLen:[%d]\n", StringStruct[i].acString, StringStruct[i].cStrLen );
	}

	printf( "%d\n",calculateNumberofLines( StringStruct, NumberOfStrings, WindowWidth ));

	arrangeString( StringStruct, NumberOfStrings, WindowWidth,calculateNumberofLines( StringStruct, NumberOfStrings, WindowWidth ));

	getch( );

}
