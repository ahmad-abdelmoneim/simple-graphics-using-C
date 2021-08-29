#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "graphics.h"


int main()
{
    int x = 15,y=35,i=0;
    int offset =25;
    int Width = 6;
    int width =500, height=700, channels=3 ;
    IMGinfo imgInfo = {width,height,channels};

    unsigned char *img = malloc(channels*height*width *sizeof(char));
    memset((void*)img,255,channels*width*height);

    // background
    //point sky[7] = {Point(10,0),Point(10,100),Point(150,150),Point(350,110),Point(450,120),Point(490,100),Point(490,0)};
    drawRectangle(imgInfo,img,Point(10,10),480,680,0xDAF2FC);


    // sun and lights
    drawCircile(imgInfo,img,Point(400,125),60,0xFAA314);

    drawLine(imgInfo,img,creatLine(Point(315,150),Point(195,190)),Width,0xFAA314);
    drawLine(imgInfo,img,creatLine(Point(323,170),Point(200,240)),Width,0xFAA314);
    drawLine(imgInfo,img,creatLine(Point(335,190),Point(240,275)),Width,0xFAA314);

    // CLOUD
    drawCircile(imgInfo,img,Point(105,90),30,0xFFFFFF);
    drawCircile(imgInfo,img,Point(150,100),45,0xFFFFFF);
    drawCircile(imgInfo,img,Point(190,100),35,0xFFFFFF);

    point  tri1[3] = {Point(1+offset,650),Point(250+offset,650),Point(125+offset,280)};
    point  tri2[3] = {Point(200+offset,650),Point(450+offset,650),Point(325+offset,350)};
    point  tri3[3] = {Point(125+offset,650),Point(350+offset,650),Point(225+offset,400)};
    point  tri4[3] = {Point(200+offset,650),Point(250+offset,650),Point(225+offset,590)};


    //arrows
/*
    point * arrow = malloc(6*sizeof(point));
    for(i=0;i<11;i++,y+=60){
            arrow[0] = Point(x,y);
            arrow[1] = Point(x+15,y-15);
            arrow[2] = Point(x+30,y);
            arrow[3] = Point(x+30,y+30);
            arrow[4] = Point(x+15,y+45) ;
            arrow[5] = Point(x,y+30);

         drawPolygonOutline(imgInfo,img,createPolygon(arrow,6),4,0x60A4B9);

         }
         free(arrow);*/

    //star shape
    point star[8] = {Point(x,y+25),Point(x+12,y+17),Point(x+25,y),Point(x+38,y+17),Point(x+50,y+25),Point(x+38,y+33),Point(x+25,y+50),Point(x+12,y+33)};
    drawPolygon(imgInfo,img,createPolygon(star,8),0xC83D23);
    //triangles
    drawPolygon(imgInfo,img,createPolygon(tri3,3),0xC83D23);
    drawPolygon(imgInfo,img,createPolygon(tri1,3),0x3C1F8E);
    drawPolygon(imgInfo,img,createPolygon(tri2,3),0x45A65B);
    drawPolygon(imgInfo,img,createPolygon(tri4,3),0xEACA04);


    stbi_write_jpg("Art.jpg", width, height,3,img,100);
        free(img);
    return 0;
}
