#include "window.h"

#define KOD_LEWYGORA	0xc9
#define KOD_POZIOMY		0xcd
#define KOD_PRAWYGORA	0xbb
#define KOD_PIONOWY		0xba
#define KOD_LEWYDOL		0xc8
#define KOD_PRAWYDOL	0xbc

void drawWindow(int x, int y, int w, int h, unsigned short kolor, const char *name)
{
	int i,j;

	setActiveColor( kolor );

	putCharXY( x, y, KOD_LEWYGORA );
	for( i=0; i<w-2; i++ )
		printf( "%c", KOD_POZIOMY );
	printf( "%c", KOD_PRAWYGORA );
	for( j=y+1; j<y+h-1; j++ )
	{
		putCharXY( x, j, KOD_PIONOWY );
		for( i=0; i<w-2; i++ )
			printf( " " );
		printf( "%c", KOD_PIONOWY );
	}
	putCharXY( x, y+h-1, KOD_LEWYDOL );
	for( i=0; i<w-2; i++ )
		printf( "%c", KOD_POZIOMY );
	printf( "%c", KOD_PRAWYDOL );

	if( name )
	{
		putStrXY( x+0.5*(w-strlen( name )),y, name );
	}
}

void clrWindow(int x, int y, int w, int h, unsigned short kolor){
    int i=x+1;
    setActiveColor(kolor);
    y+=1;
    for(y; y<h; y+=1){
        x=i;
        for(x; x<w; x++){
            setConsole(x,y);
            printf(" ");
        }
    }
}
