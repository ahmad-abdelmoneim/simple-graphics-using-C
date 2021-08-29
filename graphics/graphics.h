struct imageinfo{
    int width;
    int height;
    int channels;
};
typedef struct imageinfo IMGinfo;

struct point {
    int x;
    int y;
};
typedef struct point point;

struct line{
    char specialCase;
    int c;
    double slope;
    point start;
    point end;
};
typedef struct line line;

struct polygon{
    point * points;
    line * lines ;
    int points_num;
    int ymin,ymax,xmin,xmax;
};
typedef struct polygon polygon;

struct bounds{
    int * pointsX;
    int intersctions_num;
    char type;
};
typedef struct bounds bounds;

line creatLine(point start,point end);
point lineIntersction(line * line1,line * line2);
inline point Point(int x,int y);
void drawLine(IMGinfo info,void * imgp,line LINE,unsigned int width,long RGB);
void drawCircile(IMGinfo info,void * imgp,point center,int radius,long RGB);
void drawRectangle(IMGinfo info,void * imgp,point base,int width,int height,long RGB);

polygon createPolygon(point * points,int points_num);
void drawPolygon(IMGinfo info,void * img,polygon poly,long RGB);
int isInside(point Point,polygon poly);
int isInRange(point test,line * Line);
point getXbounds(int y,polygon poly);
int isInArray(int * array,int len,int number);
bounds getXBounds(int y,polygon poly);
int inline Y(int x,line * LINE);
void drawPolygonOutline(IMGinfo info,void * img,polygon poly,unsigned int width,long RGB);
void bubbleSort(int * array , int len);
unsigned char gradeint(int height , int y,unsigned char CCH);
