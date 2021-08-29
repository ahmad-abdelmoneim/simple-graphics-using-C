#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include <math.h>

line creatLine(point start,point end){
    line LINE;
    LINE.start = start;
    LINE.end = end ;

    if(start.x == end.x)
        {
            LINE.specialCase ='v';
        }
    else if(start.y == end.y ) {
            LINE.specialCase = 'h';
            LINE.slope =0;
            LINE.c = -start.y;
    }
    else
    {
        LINE.specialCase = 'n';
    LINE.slope = (-(end.y-start.y))/(double)(end.x-start.x);
    LINE.c = -start.y - ceil((LINE.slope)*start.x);
    }

    return LINE;
}

point Point(int x,int y)
{ return (point){x,y};}

polygon createPolygon(point * points,int points_num){

    polygon ret;
    ret.points = points;
    ret.points_num = points_num;

    ret.xmax = points[0].x;
    ret.xmin = points[0].x;

    ret.ymax =points[0].y;
    ret.ymin = points[0].y;

    ret.lines = (line *)malloc(points_num * sizeof(line));
    int i,j;
    for(i=0;i<points_num;i++){
        j= i==(points_num-1)?0:(i+1);
        ret.lines[i] = creatLine(points[i],points[j]);

    }


    for(i=0;i<points_num;i++){

        ret.xmax = (points[i].x > ret.xmax)?points[i].x : ret.xmax;
        ret.xmin = (points[i].x < ret.xmin )? points[i].x : ret.xmin;

        ret.ymax = (points[i].y > ret.ymax)?points[i].y : ret.ymax;
        ret.ymin = (points[i].y < ret.ymin )? points[i].y : ret.ymin;
    }

    return ret;
}

point lineIntersction(line * line1,line *line2){

    int x,y;
    if ((line1->specialCase =='v') && (line2->specialCase =='v'))
    {
        x=-1;
        y=-1;
    }
    else if( (line1->specialCase =='v') || (line2->specialCase =='v') )
        {
            line * vertical;
            line* inclined;
            if(line1->specialCase == 'v')
            {
                    vertical=line1;
                    inclined=line2;
            }
            else
            {
                    vertical=line2;
                    inclined=line1;
            }
            x = vertical->start.x;
            y = ceil(-( (inclined->slope * x) + inclined->c));
        }
    else if(line1->slope == line2->slope){
        x=-1;
        y=-1;
    }

    else{

    x = ceil( ((line2->c - line1->c))/(double)(line1->slope - line2->slope) );
    y = ceil(-((line1->slope * x) + line1->c));
    }
    point intersection = {x,y};
    return intersection;

}

void drawLine(IMGinfo info,void * imgp,line LINE,unsigned int width,long RGB){
    int x,y;
    int displacment ;
    printf("type %c \n",LINE.specialCase);
    if (LINE.specialCase == 'v'){ //vertical Line x=const
        displacment = LINE.start.y < LINE.end.y?1:-1;
        x = LINE.start.x;
        for(y=LINE.start.y;(y-LINE.end.y)!=0;y+=displacment){
             drawCircile(info,imgp,Point(x,y),width/2,RGB);
        }
    }
    else if(LINE.specialCase == 'h')
        {
             displacment = LINE.start.x<LINE.end.x?1:-1;
             y = LINE.start.y;
             for(x=LINE.start.x ; (x-LINE.end.x)!=0 ; x+=displacment)
             {
                drawCircile(info,imgp,Point(x,y),width/2,RGB);
             }
        }
    else
    {
        displacment = LINE.start.x<LINE.end.x?1:-1;

        for( x=LINE.start.x ; (x-LINE.end.x)!=0 ; x+=displacment)
        {
            y = Y(x,&LINE) ;
            drawCircile(info,imgp,Point(x,y),width/2,RGB);
        }
    }
}
void drawCircile(IMGinfo info,void * imgp,point center,int radius,long RGB){

    unsigned char (*imgptr)[info.width*3] = imgp;
    unsigned int x;
    unsigned int y;
    unsigned char rgb[3];

    rgb[0] = (unsigned char)(RGB>>16)&255;
    rgb[1] = (unsigned char)(RGB>>8)&255;
    rgb[2] = (unsigned char)(RGB)&255;
    long x2y2=0;
    long r2 =0;
    int Ymin,Ymax,Xmax,Xmin;
    Ymin = center.y - radius;
    Ymax = center.y +radius;

    Xmin = center.x - radius;
    Xmax = center.x + radius ;

    for( y= Ymin ; y <= Ymax ;y++)
    {
        for(x = Xmin ; x <= Xmax ;x++)
            {
                int rgbIndex = x*3;
                x2y2 = ( (center.x-x)*(center.x-x) + (center.y-y)*(center.y-y)) ;
                r2 = radius * radius;
                if ( (x2y2<=r2)&& (x<=info.width) &&(x>=0)&&(y>=0)&&(y<=info.height))
                {
                imgptr[y][rgbIndex]   = rgb[0];
                imgptr[y][++rgbIndex] = rgb[1];
                imgptr[y][++rgbIndex] = rgb[2];
                }
            }
    }
}
void drawRectangle(IMGinfo info,void * imgp,point base,int width,int height,long RGB){

    unsigned char (*imgptr)[info.width*3] = imgp;
    unsigned int x;
    unsigned int y;
    int i;
    unsigned char rgb[3];

    rgb[0] = (unsigned char)(RGB>>16)&255;
    rgb[1] = (unsigned char)(RGB>>8)&255;
    rgb[2] = (unsigned char)(RGB)&255;

    int Ymin,Ymax,Xmax,Xmin;

    Ymin = base.y;
    Ymax = base.y +height;

    Xmin = base.x;
    Xmax = base.x + width ;

    for(y= Ymin ; y <= Ymax ;y++){
        for(x = Xmin ; x <= Xmax ;x++)
            {
                int rgbIndex = x*3;
                imgptr[y][rgbIndex]   = rgb[0];
                imgptr[y][++rgbIndex] = rgb[1];
                imgptr[y][++rgbIndex] = rgb[2];
            }
        for(i=0;i<3;i++)
            {

            }
}
}
void drawPolygonOutline(IMGinfo info,void * img,polygon poly,unsigned int width,long RGB){
    int i ;
    for(i=0;i<poly.points_num;i++){
        drawLine(info,img,poly.lines[i],width,RGB);
    }
}
void plot(IMGinfo info,char * img,int *x,int*y,int len,unsigned int width,long RGB){
    int index=0;
    for(index=0;index<(len-1);index++){
        drawLine(info,img,creatLine(Point(x[index],y[index]),Point(x[index+1],y[index+1])),width,RGB);
    }
}

void drawPolygon(IMGinfo info,void * img,polygon poly,long RGB){

   unsigned char (*imgptr)[info.width*3] = img;


    unsigned char rgb[3];

    rgb[0] = (unsigned char)(RGB>>16)&255;
    rgb[1] = (unsigned char)(RGB>>8)&255;
    rgb[2] = (unsigned char)(RGB)&255;

    int rgbIndex,y,x,i;
    int Idisplacment;
    point Xbounds;
    bounds XB;
    for(y = poly.ymin ; y <= poly.ymax ;y++)
        {
            //Xbounds = getXbounds(y,poly);
            XB = getXBounds(y,poly);
            Idisplacment = XB.type =='r'?1:2;

           for (i=0; i< XB.intersctions_num ; i+=Idisplacment)
                {
                    if(i+1 < XB.intersctions_num){


                        for(x = XB.pointsX[i] ; x <= XB.pointsX[i+1] ;x++)
                        {


                            rgbIndex = x*3;
                            imgptr[y][rgbIndex]   = rgb[0];
                            imgptr[y][++rgbIndex] = rgb[1];
                            imgptr[y][++rgbIndex] = rgb[2];

                        }
                    }
                }
        }
        free(XB.pointsX);
    free(poly.lines);
}

int isInside(point testPoint,polygon poly){

    if (poly.lines != NULL) {
            point inf = { (poly.xmax+2) , testPoint.y };
            line HzLine = creatLine( testPoint,inf);

            int intersctions=0,i=0,j ;
            point crossPoint = {-1,-1};
            point * cross = malloc(sizeof(point));

            for(i=0; i < poly.points_num ;i++)
                {

                    crossPoint = lineIntersction( &HzLine ,poly.lines+i);

                    if ( (crossPoint.x >= testPoint.x) && isInRange(crossPoint,poly.lines+i))

                    {
                        cross = realloc(cross,sizeof(point) *(intersctions+1));
                        cross[intersctions++] = crossPoint;
                    }
                }

       /* int dublicated=0;
        for(i=0;i<intersctions;i++)
        {
                for(j=0;j<intersctions;j++)
                {
                    if(i!=j)
                    {
                        if( (cross[i].x==cross[j].x)&& (cross[i].y==cross[j].y) ) ++dublicated;
                    }
                }
        }

        intersctions-= (dublicated/2);
        */
        free(cross);
        return (intersctions%2)?1:0;}
    else return 0;
}

int isInRange(point test , line * Line){

    int xmax = (Line->start.x) > (Line->end.x) ? (Line->start.x): (Line->end.x);
    int xmin = Line->start.x < Line->end.x?Line->start.x:Line->end.x;

    int ymax = Line->start.y > Line->end.y?Line->start.y:Line->end.y;
    int ymin = Line->start.y < Line->end.y?Line->start.y:Line->end.y;

    return ( (test.x >= xmin)&&(test.x<=xmax) && (test.y >= ymin)&&(test.y<=ymax) )? 1:0;
}

int  Y(int x,line * LINE){
   return ceil(-((LINE->slope * x ) +LINE->c)) ;
}
int X(int y,line * LINE){
    return (-y-LINE->c)/(double)(LINE->slope);
}

point getXbounds(int y,polygon poly){

    int intersctions=0;
    int i;
    line HzLine = creatLine(Point(poly.xmin,y),Point(poly.xmax,y));
    point crossPoint = {-1,-1};


        point * cross = malloc(sizeof(point));
        for(i=0; i < poly.points_num ;i++){

            crossPoint = lineIntersction( &HzLine ,poly.lines+i);

            if( isInRange(crossPoint,poly.lines+i) )
                {

                    cross = realloc(cross,sizeof(point) *(intersctions+1));
                    cross[intersctions++] = crossPoint;
                }
        }
       int xmin = cross[0].x;
       int xmax = cross[0].x;

        for(i=0;i<intersctions;i++){
                       xmin = cross[i].x< xmin ? cross[i].x : xmin;
                       xmax = cross[i].x> xmin ? cross[i].x : xmax;
                    }
    free(cross);

    return (point){xmin,xmax};
}
bounds getXBounds(int y,polygon poly){
    int intersctions=0;
    int i,j;
    line HzLine = creatLine( Point(poly.xmin,y),Point(poly.xmax,y));
    point crossPoint = {-1,-1};
    int * cross = malloc(sizeof(int));

    for(i=0; i < poly.points_num ;i++)
    {
        crossPoint = lineIntersction( &HzLine ,poly.lines+i);

        if(isInRange(crossPoint,poly.lines+i))
            {
                ++intersctions;
                cross = realloc(cross,sizeof(int)*intersctions);
                cross[intersctions-1] = crossPoint.x;
            }
    }



        // arranging
        bubbleSort(cross,intersctions);
        // check for redundancy
        int dublicated=0;

        for(i=0;i<intersctions;i++){
            for(j=0;j<intersctions;j++){
                if(i!=j){
                    if( cross[i] == cross[j]) ++dublicated;
                }
            }
            }

            bounds Xbounds;
        // handling redundancy
        if( dublicated !=0 ){
            int count = 0;
            int mcIndex=0;
            int * mergedCross = malloc(sizeof(int));
            mergedCross[0]=-1;
            for(i=0;i<intersctions;i++)
            {
                    if(!isInArray(mergedCross,count,cross[i]))
                    {
                        count++;
                        mergedCross = realloc(mergedCross,sizeof(int)*count);
                        mergedCross[mcIndex++] = cross[i];
                    }
            }


            free(cross);
            Xbounds.intersctions_num = count;
            Xbounds.pointsX = mergedCross;
            Xbounds.type = 'r';
        }
        else{
            Xbounds.intersctions_num = intersctions;
            Xbounds.pointsX = cross;
            Xbounds.type = 'n';

        }


    return Xbounds;


}
int isInArray(int * array,int len,int number){
    int i=0;
    int found=0;
    for(i=0;i<len;i++ ){
        if(array[i] == number) {
            found = 1;
            break;
        }
    }
    return found;
}
void bubbleSort(int * array , int len){
    int i,j;
    int lastMinus_1 = len-1;
    for(i=0;i<lastMinus_1;i++)
    {
            for(j=0;j<lastMinus_1;j++)
            {
                int temp =0;
                if( array[j] > array[j+1] )
                {
                    temp = array[j];
                    array[j] = array[j+1];
                    array[j+1] = temp;
                }
            }
    }
}
unsigned char gradeint(int height , int y,unsigned char cch){
    return ((y/(double)height)*(255-cch) )+cch;
    }
