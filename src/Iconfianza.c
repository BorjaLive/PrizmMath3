//#include "cashelp.h"
#include <color.h>

#define DECIMALS 6

char **main_menu;
char **intervalos_menu;
char **critica_menu;
char **unapob_menu;
char **dospob_menu;
char **tablas_menu;

void calculate_g(double Sx, double Sy, int Nx, int Ny, double *g){
	double DIVx = Sx/Nx, DIVy = Sy/Ny;
	*g = (DIVx+DIVy)*(DIVx+DIVy);
	*g /= ((DIVx*DIVx)/(Nx+1))+((DIVy*DIVy)/(Ny+1));
	*g -= 2;
}
void calculate_s2(double Sx, double Sy, int Nx, int Ny, double *s2){
	*s2 = (((Nx-1)*Sx)+((Ny-1)*Sy))/(Nx+Ny-2);
}

void start_memory(){
	int i;
	
	main_menu = malloc(6 * sizeof(char*));
	for (i = 0; i < 6; i++)
	    main_menu[i] = malloc(24 * sizeof(char)); //Importante los dos espacios
	strcpy(main_menu[0], "  Intervalos confianza");
	strcpy(main_menu[1], "  Region critica");
	strcpy(main_menu[2], "  Test Shapiro-Wilks");
	strcpy(main_menu[3], "  Buscar en tablas");
	strcpy(main_menu[4], "  Introducir datos");
	strcpy(main_menu[5], "  Regresion lin sim");
	
	
	intervalos_menu = malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++)
	    intervalos_menu[i] = malloc(24 * sizeof(char));
	strcpy(intervalos_menu[0], "  u,s conocida");
	strcpy(intervalos_menu[1], "  u,s desconocida");
	strcpy(intervalos_menu[2], "  s^2");
	strcpy(intervalos_menu[3], "  ux-uy,sx sy conocida");
	strcpy(intervalos_menu[4], "  ux-uy,sx = sy desco...");
	strcpy(intervalos_menu[5], "  ux-uy,sx != sy des...");
	strcpy(intervalos_menu[6], "  s^2x/s^2y");
	
	
	critica_menu = malloc(2 * sizeof(char*));
	for (i = 0; i < 2; i++)
	    critica_menu[i] = malloc(24 * sizeof(char));
	strcpy(critica_menu[0], "  Una poblacion");
	strcpy(critica_menu[1], "  Dos poblaciones");
	
	unapob_menu = malloc(9 * sizeof(char*));
	for (i = 0; i < 9; i++)
	    unapob_menu[i] = malloc(24 * sizeof(char));
	strcpy(unapob_menu[0], "  u = u0 vs u != u0, s");
	strcpy(unapob_menu[1], "  u = u0 vs u > u0, s");
	strcpy(unapob_menu[2], "  u = u0 vs u < u0, s");
	strcpy(unapob_menu[3], "  u = u0 vs u != u0, !s");
	strcpy(unapob_menu[4], "  u = u0 vs u > u0, !s");
	strcpy(unapob_menu[5], "  u = u0 vs u < u0, !s");
	strcpy(unapob_menu[6], "  s = s0 vs s != s0");
	strcpy(unapob_menu[7], "  s = s0 vs s > s0");
	strcpy(unapob_menu[8], "  s = s0 vs s < s0");
	
	dospob_menu = malloc(12 * sizeof(char*));
	for (i = 0; i < 12; i++)
	    dospob_menu[i] = malloc(24 * sizeof(char));
	strcpy(dospob_menu[0], "  ux-uy=a vs != a,con s");
	strcpy(dospob_menu[1], "  ux-uy=a vs  > a,con s");
	strcpy(dospob_menu[2], "  ux-uy=a vs  < a,con s");
	strcpy(dospob_menu[3], "  ux-uy=a vs != a,sx=xy");
	strcpy(dospob_menu[4], "  ux-uy=a vs  > a,sx=xy");
	strcpy(dospob_menu[5], "  ux-uy=a vs  < a,sx=xy");
	strcpy(dospob_menu[6], "  ux-uy=a vs != a,sx!xy");
	strcpy(dospob_menu[7], "  ux-uy=a vs  > a,sx!xy");
	strcpy(dospob_menu[8], "  ux-uy=a vs  < a,sx!xy");
	strcpy(dospob_menu[9], "  sx = sy vs sx != sy");
	strcpy(dospob_menu[10], "  sx = sy vs sx  > sy");
	strcpy(dospob_menu[11], "  sx = sy vs sx  < sy");
	
	tablas_menu = malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++)
	    tablas_menu[i] = malloc(24 * sizeof(char));
	strcpy(tablas_menu[0], "  T. Normal (acumulada)");
	strcpy(tablas_menu[1], "  T. Normal (valor)");
	strcpy(tablas_menu[2], "  T. T-Student");
	strcpy(tablas_menu[3], "  T. Chi cuadrado");
	strcpy(tablas_menu[4], "  T. F-Snedecor");
	strcpy(tablas_menu[5], "  T. Coeficientes W");
	strcpy(tablas_menu[6], "  T. Valores criticos W");
}

void menu_regLin(){
	clearDisplay();
	int cantidad, i = 0, pos = 3;
	double cant, datoX, datoY, covarianza = 0.0, varianzaE, b1, b0, cofR;
	double mediaX = 0, varianzaX = 0, cvarianzaX, mediaY = 0, varianzaY = 0, cvarianzaY;
	printText(1,1,"Cantidad de datos:");
	readDouble(1,2, &cant);
	cantidad = (int)cant;
	for(; i < cantidad; i++){
		printText(1,pos,"X:");
		readDouble(4,pos, &datoX);
		printText(11,pos,"Y:");
		readDouble(14,pos, &datoY);
		pos ++;
		if(pos == 9){
			pos = 1;
			clearDisplay();
		}
		mediaX += datoX/cantidad;
		varianzaX += datoX*datoX/cantidad;
		mediaY += datoY/cantidad;
		varianzaY += datoY*datoY/cantidad;
		covarianza += datoX*datoY/cantidad;
	}
	varianzaX -= mediaX*mediaX;
	cvarianzaX = cantidad*varianzaX/(cantidad-1);
	varianzaY -= mediaY*mediaY;
	cvarianzaY = cantidad*varianzaY/(cantidad-1);
	covarianza -= mediaX*mediaY;
	b1 = covarianza/varianzaX;
	b0 = mediaY - b1*mediaX;
	varianzaE = (cantidad*(varianzaY-varianzaX*b1*b1))/(cantidad-2);
	cofR = (covarianza*covarianza);
	cofR /= (varianzaX*varianzaY);

	
	clearDisplay();
	printText(1,1,"MediaX:");
	printDouble(9,1, mediaX, DECIMALS);
	printText(1,2,"MediaY:");
	printDouble(9,2, mediaY, DECIMALS);
	
	printText(1,4,"VarianzaX:");
	printDouble(12,4, varianzaX, DECIMALS);
	printText(1,5,"VarianzaY:");
	printDouble(12,5, varianzaY, DECIMALS);

	printText(1,7,"C VarianzaX:");
	printDouble(14,7, cvarianzaX, DECIMALS);
	printText(1,8,"C VarianzaY:");
	printDouble(14,8, cvarianzaY, DECIMALS);

	wait();
	clearDisplay();
	
	printText(1,1,"DesviacionX:");
	printDouble(14,1, sqrt(varianzaX), DECIMALS);
	printText(1,2,"DesviacionY:");
	printDouble(14,2, sqrt(varianzaY), DECIMALS);

	printText(1,4,"C DesviacionX:");
	printDouble(16,4, sqrt(cvarianzaX), DECIMALS);
	printText(1,5,"C DesviacionY:");
	printDouble(16,5, sqrt(cvarianzaY), DECIMALS);

	wait();
	clearDisplay();

	printText(1,1,"Covarianza:");
	printDouble(13,1, covarianza, DECIMALS);
	printText(1,3,"VarianzaE:");
	printDouble(12,3, varianzaE, DECIMALS);
	printText(1,5,"b1:");
	printDouble(5,5, b1, DECIMALS);
	printText(1,7,"b0:");
	printDouble(5,7, b0, DECIMALS);

	wait();
	clearDisplay();

	printText(1,1,"R2:");
	printDouble(5,1, cofR, DECIMALS);
	printText(1,3,"cR2:");
	printDouble(6,3, 1-(((1-cofR)*(cantidad-1))/(cantidad-2)), DECIMALS);

	printDouble(5,5, (covarianza*covarianza), DECIMALS);
	printDouble(5,6, (varianzaX*varianzaY), DECIMALS);
	printDouble(5,7, (covarianza*covarianza)/(varianzaX*varianzaY), DECIMALS);

	wait();
	clearDisplay();

	double significacion, t, intervalo;

	printText(1,1,"Contraste hipotesis");
	printText(1,3,"Significacion:");
	readDouble(1,4, &significacion);

	table_getTvalue(cantidad-2, 1-(significacion/2), &t);
	intervalo = sqrt(varianzaE/(varianzaX*cantidad))*t;

	clearDisplay();
	printText(1,1,"Region critica");
	printText(1,3,"b1 >");
	printText(1,4,"b1 <");
	printDouble(6,3, intervalo, DECIMALS);
	printDouble(6,4, -intervalo, DECIMALS);

	if(b1 > intervalo || b1 < -intervalo)
		printTextExt(5,6,TEXT_COLOR_GREEN,"  b1 != 0");
	else
		printTextExt(5,6,TEXT_COLOR_RED,"  b1 = 0");

	wait();

	intervalo = sqrt(varianzaE*((1.0/cantidad)+((mediaX*mediaX)/(cantidad*varianzaX))))*t;

	clearDisplay();
	printText(1,1,"Region critica");
	printText(1,3,"b0 >");
	printText(1,4,"b0 <");
	printDouble(6,3, intervalo, DECIMALS);
	printDouble(6,4, -intervalo, DECIMALS);

	if(b0 > intervalo || b0 < -intervalo)
		printTextExt(5,6,TEXT_COLOR_GREEN,"  b0 != 0");
	else
		printTextExt(5,6,TEXT_COLOR_RED,"  b0 = 0");


	wait();
	clearDisplay();

	printText(1,1,"Intervalos confianza");
	printText(1,3,"Significacion:");
	readDouble(1,4, &significacion);

	table_getTvalue(cantidad-2, 1-(significacion/2), &t);
	intervalo = sqrt(varianzaE/(varianzaX*cantidad))*t;

	clearDisplay();
	printText(1,1,"Intervalo confianza");
	printText(1,3,"b1 >");
	printText(1,4,"b1 <");
	printDouble(6,3, b1-intervalo, DECIMALS);
	printDouble(6,4, b1+intervalo, DECIMALS);

	wait();

	intervalo = sqrt(varianzaE*((1.0/cantidad)+((mediaX*mediaX)/(cantidad*varianzaX))))*t;

	clearDisplay();
	printText(1,1,"Intervalo confianza");
	printText(1,3,"b0 >");
	printText(1,4,"b0 <");
	printDouble(6,3, b0-intervalo, DECIMALS);
	printDouble(6,4, b0+intervalo, DECIMALS);
}
void menu_testW(){
	int cantidad, i = 0, pos = 5;
	double cant, media = 0, varianza = 0, cvarianza, dato, b = 0, a, w, m, significacion;
	
	clearDisplay();
	printText(1,1,"Significacion:");
	readDouble(1,2, &significacion);
	printText(1,3,"Cantidad de datos:");
	readDouble(1,4, &cant);
	cantidad = (int)cant;
	double *data = (double*)calloc(cantidad,sizeof(double));
	
	for(; i < cantidad; i++){
		printText(1,pos,"Siguiente dato:");
		readDouble(1,pos+1, &dato);
		data[i] = dato;
		pos += 2;
		if(pos == 9){
			pos = 1;
			clearDisplay();
		}
		media += dato/cantidad;
		varianza += dato*dato/cantidad;
	}
	varianza -= media*media;
	cvarianza = cantidad*varianza/(cantidad-1);
	clearDisplay();
	quicksort(data, 0, cantidad-1);
	int k;
	if(cantidad%2 == 0){	//El truncamiento ya hace esto solo, pero no est� de m�s prevenir.
		k = cantidad/2;
	}else{
		k = (cantidad-1)/2;
	}
	for(i = 0; i < k; i++){
		table_getWvalue(i+1, cantidad, &a);
		b += (data[cantidad-i-1]-data[i])*a;
	}
	w = (b*b)/(cvarianza*(cantidad-1));
	table_getMvalue(cantidad, significacion, &m);
	free(data);
	
	printText(1,1,"W:");
	printDouble(4,1, w, DECIMALS);
	printText(1,2,"W critico:");
	printDouble(12,2, m, DECIMALS);
	if(w > m)
		printTextExt(5,4,TEXT_COLOR_GREEN,"  EXITO");
	else
		printTextExt(5,4,TEXT_COLOR_RED,"  FRACASO");
	
	printText(8,8,"--> Siguiente");
	wait();
	clearDisplay();
	printText(1,1,"Media:");
	printDouble(8,1, media, DECIMALS);
	printText(1,3,"Varianza:");
	printDouble(11,3, varianza, DECIMALS);
	printText(1,4,"C Varianza:");
	printDouble(13,4, cvarianza, DECIMALS);
	printText(1,6,"Desviacion:");
	printDouble(13,6, sqrt(varianza), DECIMALS);
	printText(1,7,"C Desviacion:");
	printDouble(15,7, sqrt(cvarianza), DECIMALS);
}
void menu_ingresar(){
	clearDisplay();
	int cantidad, i = 0, pos = 3;
	double cant, media = 0, varianza = 0, cvarianza, dato;
	printText(1,1,"Cantidad de datos:");
	readDouble(1,2, &cant);
	cantidad = (int)cant;
	for(; i < cantidad; i++){
		printText(1,pos,"Siguiente dato:");
		readDouble(1,pos+1, &dato);
		pos += 2;
		if(pos == 9){
			pos = 1;
			clearDisplay();
		}
		media += dato/cantidad;
		varianza += dato*dato/cantidad;
	}
	varianza -= media*media;
	cvarianza = cantidad*varianza/(cantidad-1);
	clearDisplay();
	printText(1,1,"Media:");
	printDouble(8,1, media, DECIMALS);
	printText(1,3,"Varianza:");
	printDouble(11,3, varianza, DECIMALS);
	printText(1,4,"C Varianza:");
	printDouble(13,4, cvarianza, DECIMALS);
	printText(1,6,"Desviacion:");
	printDouble(13,6, sqrt(varianza), DECIMALS);
	printText(1,7,"C Desviacion:");
	printDouble(15,7, sqrt(cvarianza), DECIMALS);
	
}
void menu_tablas(){
	double x1, x2, a, n;
	switch(menuSelect(tablas_menu, 7)){
		case 0:	//Z prob
			clearDisplay();
			printText(1,1, "Limite superior:");
			readDouble(1,2, &x1);
			table_getZprob(x1, &n);
			printText(1,4, "Probabilidad acumulada:");
			printDouble(1, 5, n, DECIMALS);
		break;
		case 1:	//Z value
			clearDisplay();
			printText(1,1, "Probabilidad:");
			readDouble(1,2, &x1);
			clearDisplay();
			table_getZvalue(x1, &n);
			printText(1,1, "Normal tipificada Z");
			printText(1,2, "p = ");
			printDouble(5, 2, x1, DECIMALS);
			printDouble(1, 4, n, DECIMALS);
		break;
		case 2:	//T value
			clearDisplay();
			printText(1,1, "Grados de livertad:");
			readDouble(1,2, &x1);
			printText(1,3, "Probabilidad:");
			readDouble(1,4, &a);
			clearDisplay();
			table_getTvalue((int)x1, a, &n);
			printText(1,1, "T-Studednt");
			printText(1,2, "n = ");
			printDouble(5, 2, x1, 0);
			printText(1,3, "p = ");
			printDouble(5, 3, a, DECIMALS);
			printDouble(1, 5, n, DECIMALS);
		break;
		case 3:	//X value
			clearDisplay();
			printText(1,1, "Grados de livertad:");
			readDouble(1,2, &x1);
			printText(1,3, "Probabilidad:");
			readDouble(1,4, &a);
			clearDisplay();
			table_getXvalue((int)x1, a, &n);
			printText(1,1, "Chi cuadrado X");
			printText(1,2, "n = ");
			printDouble(5, 2, x1, 0);
			printText(1,3, "p = ");
			printDouble(5, 3, a, DECIMALS);
			printDouble(1, 5, n, DECIMALS);
		break;
		case 4:	//F value
			clearDisplay();
			printText(1,1, "Grados de livertad 1:");
			readDouble(1,2, &x1);
			printText(1,3, "Grados de livertad 2:");
			readDouble(1,4, &x2);
			printText(1,5, "Probabilidad:");
			readDouble(1,6, &a);
			clearDisplay();
			table_getFvalue((int)x1, (int)x2, a, &n);
			printText(1,1, "F-Snedecor");
			printText(1,2, "n = ");
			printDouble(5, 2, x1, 0);
			printText(1,3, "m = ");
			printDouble(5, 3, x2, 0);
			printText(1,4, "p = ");
			printDouble(5, 4, a, DECIMALS);
			printDouble(1, 6, n, DECIMALS);
		break;
		case 5:	//W value
			clearDisplay();
			printText(1,1, "Valor de i:");
			readDouble(1,2, &x1);
			printText(1,3, "Valor de n:");
			readDouble(1,4, &x2);
			clearDisplay();
			table_getWvalue((int) x1, (int) x2, &n);
			printText(1,1, "Coeficiente W");
			printText(1,2, "i = ");
			printDouble(5, 2, x1, 0);
			printText(1,3, "n = ");
			printDouble(5, 3, x2, 0);
			printDouble(1, 5, n, DECIMALS);
		break;
		case 6:	//M value
			clearDisplay();
			printText(1,1, "Valor de n:");
			readDouble(1,2, &x1);
			printText(1,3, "Probabilidad:");
			readDouble(1,4, &a);
			clearDisplay();
			table_getMvalue((int) x1, a, &n);
			printText(1,1, "Valor critico W");
			printText(1,2, "n = ");
			printDouble(5, 2, x1, 0);
			printText(1,3, "p = ");
			printDouble(5, 3, a, DECIMALS);
			printDouble(1, 5, n, DECIMALS);
		break;
		case -1: //Regresar
			menu_main();
		break;
	}
}
void menu_dospob(){
	double diferencia0, varianzaX, varianzaY, muestrasX, muestrasY, significacion, z, intervalo, Sp, g, f1, f2;
	int gR;
	switch(menuSelect(dospob_menu, 12)){
		case 0:	//ux-uy=a vs != a,con s
			clearDisplay();
			printText(1,1,"Varianza X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"Varianza Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getZvalue(1-(significacion/2), &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printText(1,5,"X - Y >=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
			printDouble(10,5, diferencia0+intervalo, DECIMALS);
		break;
		case 1: //ux-uy=a vs  > a,con s
			clearDisplay();
			printText(1,1,"Varianza X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"Varianza Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getZvalue(1-significacion, &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y >=");
			printDouble(10,3, diferencia0+intervalo, DECIMALS);
		break;
		case 2: //ux-uy=a vs  < a,con s
			clearDisplay();
			printText(1,1,"Varianza X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"Varianza Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getZvalue(1-significacion, &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
		break;
		case 3: //ux-uy=a vs != a,sx=xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestrasX+muestrasY-2), 1-(significacion/2), &z);
			calculate_s2(varianzaX, varianzaY, (int)muestrasX, (int)muestrasY, &Sp);
			intervalo = sqrt(Sp)*sqrt((1/muestrasX)+(1/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printText(1,5,"X - Y >=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
			printDouble(10,5, diferencia0+intervalo, DECIMALS);
			printText(1,8,"Sp = ");
			printDouble(6,8, sqrt(Sp), DECIMALS);
		break;
		case 4: //ux-uy=a vs  > a,sx=xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestrasX+muestrasY-2), 1-significacion, &z);
			calculate_s2(varianzaX, varianzaY, (int)muestrasX, (int)muestrasY, &Sp);
			intervalo = sqrt(Sp)*sqrt((1/muestrasX)+(1/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y >=");
			printDouble(10,3, diferencia0+intervalo, DECIMALS);
			printText(1,7,"Sp = ");
			printDouble(6,7, sqrt(Sp), DECIMALS);
		break;
		case 5: //ux-uy=a vs  < a,sx=xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestrasX+muestrasY-2), 1-significacion, &z);
			calculate_s2(varianzaX, varianzaY, (int)muestrasX, (int)muestrasY, &Sp);
			intervalo = sqrt(Sp)*sqrt((1/muestrasX)+(1/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
			printText(1,7,"Sp = ");
			printDouble(6,7, sqrt(Sp), DECIMALS);
		break;
		case 6: //ux-uy=a vs != a,sx!xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			calculate_g(varianzaX, varianzaY, (int) muestrasX, (int) muestrasY, &g);
			reround(g, &gR);
			table_getTvalue(gR, 1-(significacion/2), &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printText(1,5,"X - Y >=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
			printDouble(10,5, diferencia0+intervalo, DECIMALS);
			printText(1,8,"g = ");
			printDouble(5,8, g, DECIMALS);
		break;
		case 7: //ux-uy=a vs  > a,sx!xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			calculate_g(varianzaX, varianzaY, (int) muestrasX, (int) muestrasY, &g);
			reround(g, &gR);
			table_getTvalue(gR, 1-significacion, &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y >=");
			printDouble(10,3, diferencia0+intervalo, DECIMALS);
			printText(1,8,"g = ");
			printDouble(5,8, g, DECIMALS);
		break;
		case 8: //ux-uy=a vs  < a,sx!xy
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Diferencia0:");
			readDouble(1,2, &diferencia0);
			printText(1,3,"Significacion:");
			readDouble(1,4, &significacion);
			clearDisplay();
			calculate_g(varianzaX, varianzaY, (int) muestrasX, (int) muestrasY, &g);
			reround(g, &gR);
			table_getTvalue(gR, 1-significacion, &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X - Y <=");
			printDouble(10,3, diferencia0-intervalo, DECIMALS);
			printText(1,8,"g = ");
			printDouble(5,8, g, DECIMALS);
		break;
		case 9: //sx = sy vs sx != sy
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getFvalue((int) muestrasX-1, (int) muestrasY-1, 1-(significacion/2), &f1);
			table_getFvalue((int) muestrasY-1, (int) muestrasX-1, 1-(significacion/2), &f2);
			printText(1,1,"Region critica:");
			printText(1,3,"S2cx/S2cy <=");
			printText(1,5,"S2cx/S2cy >=");
			printDouble(14,3, 1/f2, DECIMALS);
			printDouble(14,5, f1, DECIMALS);
		break;
		case 10://sx = sy vs sx  > sy
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getFvalue((int) muestrasX-1, (int) muestrasY-1, 1-significacion, &f1);
			printText(1,1,"Region critica:");
			printText(1,3,"S2cx/S2cy >=");
			printDouble(14,3, f1, DECIMALS);
		break;
		case 11://sx = sy vs sx  < sy
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getFvalue((int) muestrasY-1, (int) muestrasX-1, 1-significacion, &f2);
			printText(1,1,"Region critica:");
			printText(1,3,"S2cx/S2cy <=");
			printDouble(14,3, 1/f2, DECIMALS);
		break;
		case -1:
			menu_critica();
		break;
	}
}
void menu_unapob(){
	double media, desviacion, muestras, significacion, z, intervalo, varianza, x1, x2;
	switch(menuSelect(unapob_menu, 9)){
		case 0:	// u = u0 vs u != u0, s conocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getZvalue(1-(significacion/2), &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X <=");
			printText(1,5,"X >=");
			printDouble(6,3, media-intervalo, DECIMALS);
			printDouble(6,5, media+intervalo, DECIMALS);
		break;
		case 1:	// u = u0 vs u > u0, s conocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getZvalue(1-significacion, &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X >=");
			printDouble(6,3, media+intervalo, DECIMALS);
		break;
		case 2:	// u = u0 vs u < u0, s conocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getZvalue(1-significacion, &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X <=");
			printDouble(6,3, media-intervalo, DECIMALS);
		break;
		case 3:	// u = u0 vs u != u0, s desconocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Cuasi desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestras-1), 1-(significacion/2), &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X <=");
			printText(1,5,"X >=");
			printDouble(6,3, media-intervalo, DECIMALS);
			printDouble(6,5, media+intervalo, DECIMALS);
		break;
		case 4:	// u = u0 vs u > u0, s desconocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Cuasi desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestras-1), 1-significacion, &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X >=");
			printDouble(6,3, media+intervalo, DECIMALS);
		break;
		case 5:	// u = u0 vs u < u0, s desconocida
			clearDisplay();
			printText(1,1,"Media0:");
			readDouble(1,2, &media);
			printText(1,3,"Cuasi desviacion:");
			readDouble(1,4, &desviacion);
			printText(1,5,"Tamano muestral:");
			readDouble(1,6, &muestras);
			printText(1,7,"Significacion:");
			readDouble(1,8, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestras-1), 1-significacion, &z);
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Region critica:");
			printText(1,3,"X <=");
			printDouble(6,3, media-intervalo, DECIMALS);
		break;
		case 6:	// s = s0 vs s != s0
			clearDisplay();
			printText(1,1,"Varianza0:");
			readDouble(1,2, &varianza);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getXvalue((int)(muestras-1), 1-(significacion/2), &x1);
			table_getXvalue((int)(muestras-1), significacion/2, &x2);
			printText(1,1,"Region critica:");
			printText(1,3,"S2c >=");
			printText(1,5,"S2c <=");
			printDouble(8,3, (varianza*x1)/(muestras-1), DECIMALS);
			printDouble(8,5, (varianza*x2)/(muestras-1), DECIMALS);
		break;
		case 7:	// s = s0 vs s > s0
			clearDisplay();
			printText(1,1,"Varianza0:");
			readDouble(1,2, &varianza);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getXvalue((int)(muestras-1), 1-significacion, &z);
			printText(1,1,"Region critica:");
			printText(1,3,"S2c >=");
			printDouble(8,3, (varianza*z)/(muestras-1), DECIMALS);
		break;
		case 8:	// s = s0 vs s < s0
			clearDisplay();
			printText(1,1,"Varianza0:");
			readDouble(1,2, &varianza);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getXvalue((int)(muestras-1), significacion, &z);
			printText(1,1,"Region critica:");
			printText(1,3,"S2c <=");
			printDouble(8,3, (varianza*z)/(muestras-1), DECIMALS);
		break;
		case -1:
			menu_critica();
		break;
	}
}
void menu_critica(){
	clearDisplay();
	switch(menuSelect(critica_menu, 2)){
		case 0:	//Una poblacion
			menu_unapob();
		break;
		case 1:	//Dos poblaciones independientes
			menu_dospob();
		break;
		case -1:
			menu_main();
		break;
	}
}
void menu_intervalos(){
	clearDisplay();
	double media, muestras, desviacion, significacion, z, intervalo;
	double varianza, x1, x2;
	double varianzaX, varianzaY, mediaX, mediaY, muestrasX, muestrasY, g, s2, f1, f2;
	int gR;
	switch(menuSelect(intervalos_menu, 7)){
		case 0:	//Media con desvacion conocida
			clearDisplay();
			printText(1,1,"Media muestral:");
			readDouble(1,2, &media);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Desviacion tipica:");
			readDouble(1,6, &desviacion);
			clearDisplay();
			printText(1,1,"Significacion:");
			readDouble(1,2, &significacion);
			table_getZvalue(1-(significacion/2), &z);
			clearDisplay();
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Intervalo para media");
			printText(1,2,"varianza conocida:");
			printDouble(1,4, media-intervalo, DECIMALS);
			printDouble(1,6, media+intervalo, DECIMALS);
		break;
		case 1:	//Media con desvacion desconocida
			clearDisplay();
			printText(1,1,"Media muestral:");
			readDouble(1,2, &media);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Cuasi desviacion:");
			readDouble(1,6, &desviacion);
			clearDisplay();
			printText(1,1,"Significacion:");
			readDouble(1,2, &significacion);
			table_getTvalue((int)muestras-1,1-(significacion/2), &z);
			clearDisplay();
			intervalo = (desviacion/sqrt(muestras))*z;
			printText(1,1,"Intervalo para media");
			printText(1,2,"varianza desconocida:");
			printDouble(1,4, media-intervalo, DECIMALS);
			printDouble(1,6, media+intervalo, DECIMALS);
		break;
		case 2:	//Desviacion
			clearDisplay();
			printText(1,1,"Varianza muestral:");
			readDouble(1,2, &varianza);
			printText(1,3,"Tamano muestral:");
			readDouble(1,4, &muestras);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getXvalue((int)muestras-1,1-(significacion/2), &x1);
			table_getXvalue((int)muestras-1,significacion/2, &x2);
			printText(1,1,"Intervalo para varianza:");
			printDouble(1,3, (muestras*varianza)/x1, DECIMALS);
			printDouble(1,5, (muestras*varianza)/x2, DECIMALS);
		break;
		case 3:	//Diferencia de medias, desviaciones conocidas
			clearDisplay();
			printText(1,1,"Media muestral X:");
			readDouble(1,2, &mediaX);
			printText(1,3,"Media muestral Y:");
			readDouble(1,4, &mediaY);
			printText(1,5,"Varianza X:");
			readDouble(1,6, &varianzaX);
			printText(1,7,"Varianza Y:");
			readDouble(1,8, &varianzaY);
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getZvalue(1-(significacion/2), &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Intervalo para la");
			printText(1,2,"diferencia de medias:");
			printDouble(1,4, (mediaX-mediaY)-intervalo, DECIMALS);
			printDouble(1,6, (mediaX-mediaY)+intervalo, DECIMALS);
		break;
		case 4:	//Diferencia de medias, desviaciones desconocidas e iguales
			clearDisplay();
			printText(1,1,"Media muestral X:");
			readDouble(1,2, &mediaX);
			printText(1,3,"Media muestral Y:");
			readDouble(1,4, &mediaY);
			printText(1,5,"C Varianza muestral X:");
			readDouble(1,6, &varianzaX);
			printText(1,7,"C Varianza muestral Y:");
			readDouble(1,8, &varianzaY);
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			table_getTvalue((int)(muestrasX+muestrasY-2),1-(significacion/2), &z);
			calculate_s2(varianzaX, varianzaY, (int)muestrasX, (int)muestrasY, &s2);
			intervalo = sqrt((1/muestrasX)+(1/muestrasY))*sqrt(s2)*z;
			printText(1,1,"Intervalo para la");
			printText(1,2,"diferencia de medias:");
			printDouble(1,4, (mediaX-mediaY)-intervalo, DECIMALS);
			printDouble(1,6, (mediaX-mediaY)+intervalo, DECIMALS);
			printText(1,8,"Sp:");
			printDouble(5,8, s2, DECIMALS);
		break;
		case 5:	//Diferencia de medias, desviaciones desconocidas y diferentes
			clearDisplay();
			printText(1,1,"Media muestral X:");
			readDouble(1,2, &mediaX);
			printText(1,3,"Media muestral Y:");
			readDouble(1,4, &mediaY);
			printText(1,5,"C Varianza muestral X:");
			readDouble(1,6, &varianzaX);
			printText(1,7,"C Varianza muestral Y:");
			readDouble(1,8, &varianzaY);
			clearDisplay();
			printText(1,1,"Tamano muestral X:");
			readDouble(1,2, &muestrasX);
			printText(1,3,"Tamano muestral Y:");
			readDouble(1,4, &muestrasY);
			printText(1,5,"Significacion:");
			readDouble(1,6, &significacion);
			clearDisplay();
			calculate_g(varianzaX, varianzaY, (int)muestrasX, (int)muestrasY, &g);
			reround(g, &gR);
			table_getTvalue(gR,1-(significacion/2), &z);
			intervalo = sqrt((varianzaX/muestrasX)+(varianzaY/muestrasY))*z;
			printText(1,1,"Intervalo para la");
			printText(1,2,"diferencia de medias:");
			printDouble(1,4, (mediaX-mediaY)-intervalo, DECIMALS);
			printDouble(1,5, (mediaX-mediaY)+intervalo, DECIMALS);
			printText(1,7,"g:");
			printDouble(4,7, g, DECIMALS);
		break;
		case 6:	//Relacion entre las desviaciones
			clearDisplay();
			printText(1,1,"C Varianza muestral X:");
			readDouble(1,2, &varianzaX);
			printText(1,3,"C Varianza muestral Y:");
			readDouble(1,4, &varianzaY);
			printText(1,5,"Tamano muestral X:");
			readDouble(1,6, &muestrasX);
			printText(1,7,"Tamano muestral Y:");
			readDouble(1,8, &muestrasY);
			clearDisplay();
			printText(1,1,"Significacion:");
			readDouble(1,2, &significacion);
			clearDisplay();
			intervalo = varianzaY/varianzaX;
			table_getFvalue((int)(muestrasY-1), (int)(muestrasX-1), 1-(significacion/2), &f1);
			table_getFvalue((int)(muestrasX-1), (int)(muestrasY-1), 1-(significacion/2), &f2);
			printText(1,1,"Intervalo para el");
			printText(1,2,"cociente de varianza:");
			printDouble(1,4, intervalo*(1/f1), DECIMALS);
			printDouble(1,6, intervalo*f2, DECIMALS);
		break;
		case -1:
			menu_main();
		break;
	}
}
void menu_main(){
	clearDisplay();
	switch(menuSelect(main_menu, 6)){
		case 0:	//Intervalos de confianza
			menu_intervalos();
		break;
		case 1:	//Region critica
			menu_critica();
		break;
		case 2:	//Test W
			menu_testW();
		break;
		case 3:	//Buscar en tablas
			menu_tablas();
		break;
		case 4:	//Introducir datos
			menu_ingresar();
		break;
		case 5:	//Introducir datos para regresion lineal
			menu_regLin();
		break;
		case -1: //Regresar
		break;
	}
}

void main(void) {
	start_memory();
	
	while(1){
		menu_main();
		wait();
		clearDisplay();
	}
	
	return;
}
