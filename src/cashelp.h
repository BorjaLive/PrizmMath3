#ifndef CASHELP_INCLUDE
#define CASHELP_INCLUDE

#define KEY_SIGN -0x79
#define KEY_MINUS -0x67

#define CREATEMODE_FILE 1
#define CREATEMODE_FOLDER 5
#define READ 0
#define READ_SHARE 1
#define WRITE 2
#define READWRITE 3
#define READWRITE_SHARE 4

#define FILE_PATH_tZ "\\\\fls0\\ICTABLAS\\tZ.txt"
#define FILE_PATH_tT "\\\\fls0\\ICTABLAS\\tT.txt"
#define FILE_PATH_tX "\\\\fls0\\ICTABLAS\\tX.txt"
#define FILE_PATH_tF1 "\\\\fls0\\ICTABLAS\\tF1.txt"
#define FILE_PATH_tF2 "\\\\fls0\\ICTABLAS\\tF2.txt"
#define FILE_PATH_tF3 "\\\\fls0\\ICTABLAS\\tF3.txt"
#define FILE_PATH_tF4 "\\\\fls0\\ICTABLAS\\tF4.txt"
#define FILE_PATH_tF5 "\\\\fls0\\ICTABLAS\\tF5.txt"
#define FILE_PATH_tW "\\\\fls0\\ICTABLAS\\tW.txt"
#define FILE_PATH_tM "\\\\fls0\\ICTABLAS\\tM.txt"
#define NMAX 100000
#define RAND_MAX 1000

#include <display.h>
#include <input.h>
#include <keyboard.h>
#include <color.h>

//Basic stuff
int expTen(int n);
char nthdigit(int n, int i);
int strlen(char *text);
int strcpy(char *dest, char *orig);
double sqrt(double a); //No es mia
void reround(double d, int *i);
void quicksort(double *v, int e, int d);

//C warp shit
void doubleToString(double n, int decimals, char *text);
double stringToDouble(char *text);
void stringRealToDouble(char *text, double *num);

//CASIO Prizm automate
void printText(int x, int y, char *text);
void printTextExt(int x, int y, int color, char *text);
void printDouble(int x, int y, double n, int decimals);
void readDouble(int x, int y, double *n);
void clearDisplay();
void wait();

//Menus
int menuSelect(char **menus, int n);

//Datos de las tablas
void table_getZprob(double x, double *n);
void table_getZvalue(double x, double *n);
void table_getTvalue(int x, double a, double *n);
void table_getXvalue(int x, double a, double *n);
void table_getFvalue(int x1, int x2, double a, double *n);
void table_getWvalue(int x1, int x2, double *n);
void table_getMvalue(int x, double a, double *n);

#endif
