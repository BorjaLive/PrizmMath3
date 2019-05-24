#include "cashelp.h"

int expTen(int n){
	int res = 1;
	
	while(--n >= 0) res *= 10;
	
	return res;
}
char nthdigit(int n, int i){
    while (i--) n /= 10;
    
    return (n % 10);
}
int strlen(char *text){
	int lenth = 0;
	
	while(text[lenth] != 0) lenth++;
	
	return lenth;
}
int strcpy(char *dest, char *orig){
	int lenth = strlen(orig), i = 0;
	for(; i < lenth; i++)
		dest[i] = orig[i];
	dest[i] = 0;
}
double powerOfTen(int num){
	double rst = 1.0;
	int i;
	if(num >= 0)
		for(i = 0; i < num ; i++) rst *= 10.0;
	else
		for(i = 0; i < (0 - num ); i++) rst *= 0.1;
	return rst;
}
double sqrt(double a){
	double z = a; 
	double rst = 0.0;
	int max = 8;
	int i;
	double j = 1.0;
	
	for(i = max ; i > 0 ; i--){
		 if(z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0){
			while( z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0){
				j++;
				if(j >= 10) break;
			}
			j--; //correct the extra value by minus one to j
			z -= (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)); //find value of z
			rst += j * powerOfTen(i);     // find sum of a
			j = 1.0;
		}
	 }
	for(i = 0 ; i >= 0 - max ; i--){
		if(z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0){
			while( z - (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)) >= 0) j++;
			j--;
			z -= (( 2 * rst ) + ( j * powerOfTen(i)))*( j * powerOfTen(i)); //find value of z
			rst += j * powerOfTen(i);     // find sum of a
			j = 1.0;
		}
	}
	return rst;
}
void reround(double d, int *i){
	*i = 0;
	while(d-- > 0.5) (*i)++;
}
int partition(double *v, int e, int d) {
	double x = v[e];
	int i = e - 1;
	int j = d + 1;
	double aux;
	while (1) {
		while (x < v[--j]);
		while (v[++i] < x);
		if (i >= j) return j;
		aux = v[i];
		v[i] = v[j];
		v[j] = aux;
	}
}
void quicksort(double *v, int e, int d) {
	if (e < d) {
		int q = partition(v, e, d);
		quicksort(v, e, q);
		quicksort(v, q+1, d);
	}
}



void doubleToString(double n, int decimals, char *text){
	int sign = 0;
	if(n < 0){
		sign = 1;
		n = -n;
	}
	
		int key;
	
	int divMax = 0;
	while((int)(n/expTen(divMax)) > 0) divMax++;		
		
	int i;
	for(i = divMax; i > 0; i--){
		text[divMax - i] = nthdigit(n, i-1)+KEY_CHAR_0;
	}
	if(decimals != 0)
		text[divMax] = KEY_CHAR_DP;
	for(i = 0; i < decimals; i++){
		//printText(1+i,2, "I");
		//GetKey(&key);
		text[divMax+1+i] = nthdigit(n*expTen(i+1),0)+KEY_CHAR_0;
	}
	text[divMax+1+decimals] = 0;
		
	if(sign == 1){
		for(i = divMax+1+decimals; i >= 0; i--)
			text[i+1] = text[i];
		text[0] = KEY_CHAR_MINUS;
	}
}
double stringToDouble(char *text){
	double n = 0;
	signed int sign = 1;
	
	int dot = 0;
	int i = 0;
	
	if(text[i] == KEY_CHAR_MINUS || text[i] == KEY_CHAR_PMINUS || (int)text[i] == KEY_SIGN || (int)text[i] == KEY_MINUS){
		i = 1;
		sign = -1;
	}
	
	while(text[i] != 0){
		if(text[i] == KEY_CHAR_DP){
	    	dot = 1;
		}else{
			if(dot > 0){
				n += (double)(text[i]-KEY_CHAR_0)/expTen(dot);
				dot++;
			}else{
				n = (n*10)+(text[i]-KEY_CHAR_0);
			}
		}
		i++;
	}
	
	return n*sign;
}
void stringRealToDouble(char *text, double *num){
	double n = 0;
	signed int sign = 1;
	
	int dot = 0;
	int i = 0;
	
	if(text[i] == '-'){
		i = 1;
		sign = -1;
	}
	
	while(text[i] != 0){
		if(text[i] == '.'){
	    	dot = 1;
		}else{
			if(dot > 0){
				n += (double)(text[i]-'0')/expTen(dot);
				dot++;
			}else{
				n = (n*10)+(text[i]-'0');
			}
		}
		i++;
	}
	
	*num = n*sign;
}


void printText(int x, int y, char *text){
	DisplayMBString((unsigned char*)text, 0, 0, x, y);
}
void printTextExt(int x, int y, int color, char *text){
	PrintXY(x,y,text,0,color);
}
void readDouble(int x, int y, double *n){
	char *buffer = malloc(256); // Some string length
	int start = 0; // Used for scrolling left and right
	int cursor = 0; // Cursor position
	
	buffer[0] = '\0'; // This sets the first character to \0, also represented by "", an empty string
	
	DisplayMBString((unsigned char*)buffer, start, cursor, x, y); // Last to parameters are X,Y coords (not in pixels)
	
	int key;
	while(1){
		GetKey(&key); // Blocking is GOOD.  This gets standard keys processed and, possibly, powers down the CPU while waiting
	
		if(key == KEY_CTRL_EXE){
			// Ok
			break;
		}else if(key == KEY_CTRL_EXIT){
			// Aborted
			break;
		}
	
	  	if(key && key < 30000){
		    cursor = EditMBStringChar((unsigned char*)buffer, 256, cursor, key);
		    DisplayMBString((unsigned char*)buffer, start, cursor, x,y);
	  		//printDouble(4, 4, buffer[0], 2);
	 	}else{
	    	EditMBStringCtrl((unsigned char*)buffer, 256, &start, &cursor, &key, x, y);
	  	}
	}
	
	*n = stringToDouble(buffer);
	
	free(buffer);
}

void printDouble(int x, int y, double n, int decimals){
	char text[20];
	
	doubleToString(n, decimals, (char *) &text);
	printText(x, y, (char *) &text);
}

void clearDisplay(){
	char clean[25] = "                        ";
	int i;
	for(i = 1; i <= 8; i++)
		printText(0, i, (char *) &clean);
}
void wait(){
	int key;
	GetKey(&key);
}

int menuSelect(char **menus, int n){
	int selected = 0;
	
	int key, start = 0, i;
	while(1){
		clearDisplay();
		
		for(i = 0; i < 8 && i+start < n; i++)
			printTextExt(1,i+1, i+start==selected?TEXT_COLOR_RED:TEXT_COLOR_BLACK, menus[i+start]);
		
		
		GetKey(&key);
		switch(key){
			case KEY_CTRL_DOWN:
				if(selected == n-1){
					selected = 0;
					start = 0;
				}else{
					selected++;
					if(selected > start+7)
						start++;
				}
			break;
			case KEY_CTRL_UP:
				if(selected == 0){
					selected = n-1;
					start = n-8;
					if(start < 0)
						start = 0;
				}else{
					selected--;
					if(selected < start)
						start--;
				}
			break;
			case KEY_CTRL_EXE:
				return selected;
			break;
			case KEY_CTRL_EXIT:
				return -1;
			break;
		}
	}
	
	return -1;
}



void table_getZprob(double x, double *n){
    if(x < 0){
    	table_getZprob(1-x, n);
    	return;
	}
    if(x > 4){
    	*n = 1.0;
    	return;
	}
    
    unsigned short pFile[sizeof(FILE_PATH_tZ)*2]; // Make buffer
	int hFile;
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tZ, sizeof(FILE_PATH_tZ)); 
	hFile = Bfile_OpenFile_OS(pFile, READ); // Get handle
    char num[10];
    int j;
    for(j = 0; j < 10; j++)
    	num[j] = 0;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
    
    double i;
    unsigned int pos = 0;
    for(i = 0; i < x; i+=0.01){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	j = 0;
	do{
		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
		pos++;
		if(buffer != '|'){
			num[j] = buffer;
			j++;
		}
	}while(buffer != '|');
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}
void table_getZvalue(double x, double *n){
    if(x < 0){
    	table_getZprob(1-x, n);
    	return;
	}
    if(x > 4){
    	*n = 1.0;
    	return;
	}
    
    unsigned short pFile[sizeof(FILE_PATH_tZ)*2]; // Make buffer
	int hFile;
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tZ, sizeof(FILE_PATH_tZ)); 
	hFile = Bfile_OpenFile_OS(pFile, READ); // Get handle
    char num[10];
    int j;
    for(j = 0; j < 10; j++)
    	num[j] = 0;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
    
    double i = 0, prob;
    unsigned int pos = 0;
    while(1){
		for(j = 0; j < 10; j++)
    		num[j] = 0;
    	j = 0;
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		if(buffer != '|'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != '|');
		stringRealToDouble((char *) &num, &prob);
		if(prob == x){
			*n = i;
			break;
		}else if(prob > x){
			*n = i-0.005;
			break;
		}else if(i > 4){
			*n = 4;
			break;
		}
		i+=0.01;
	}
	
	Bfile_CloseFile_OS(hFile);
}

void table_getTvalue(int x, double a, double *n){
	if(x > 100) x = 101;
	x--;
	int div;
	if(a > 0.993)
		div = 6;
	else if(a > 0.98)
		div = 5;
	else if(a > 0.973)
		div = 4;
	else if(a > 0.93)
		div = 3;
	else if(a > 0.8)
		div = 2;
	else
		div = 1;
		
		//printDouble(1, 1, (double)x, 5);
		//printDouble(1, 5, (double)div, 5);
	
	unsigned short pFile[sizeof(FILE_PATH_tT)*2]; // Make buffer
	int hFile;
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tT, sizeof(FILE_PATH_tT)); 
	hFile = Bfile_OpenFile_OS(pFile, READ); // Get handle
    char num[10];
    int j;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
    
    int countX, countDiv;
    unsigned long int pos = 0;
    for(countX = 0; countX < x; countX++){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	
    for(countDiv = 0; countDiv < div; countDiv++){
	    for(j = 0; j < 10; j++)
	    	num[j] = 0;
		j = 0;
		
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		
    		if(buffer != ';'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != ';');
	}
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}

void table_getXvalue(int x, double a, double *n){
	if(x > 200) x = 200;
	x--;
	int div;
	if(a > 0.993)
		div = 10;
	else if(a > 0.98)
		div = 9;
	else if(a > 0.973)
		div = 8;
	else if(a > 0.93)
		div = 7;
	else if(a > 0.75)
		div = 6;
	else if(a > 0.08)
		div = 5;
	else if(a > 0.03)
		div = 4;
	else if(a > 0.015)
		div = 3;
	else if(a > 0.008)
		div = 2;
	else
		div = 1;
		
		//printDouble(1, 1, (double)x, 5);
		//printDouble(1, 5, (double)div, 5);
	
	unsigned short pFile[sizeof(FILE_PATH_tX)*2]; // Make buffer
	int hFile;
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tX, sizeof(FILE_PATH_tX)); 
	hFile = Bfile_OpenFile_OS(pFile, READ); // Get handle
    char num[10];
    int j;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
    
    int countX, countDiv;
    unsigned long int pos = 0;
    for(countX = 0; countX < x; countX++){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	
    for(countDiv = 0; countDiv < div; countDiv++){
	    for(j = 0; j < 10; j++)
	    	num[j] = 0;
		j = 0;
		
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		
    		if(buffer != ';'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != ';');
	}
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}

void table_getFvalue(int x1, int x2, double a, double *n){
	int hFile;
	unsigned short pFile[sizeof(FILE_PATH_tF1)*2];
	if(a > 0.993){
	    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tF5, sizeof(FILE_PATH_tF5)); 
	}else if(a > 0.983){
	    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tF4, sizeof(FILE_PATH_tF4)); 
	}else if(a > 0.965){
	    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tF3, sizeof(FILE_PATH_tF3)); 
	}else if(a > 0.925){
	    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tF2, sizeof(FILE_PATH_tF2)); 
	}else{
	    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tF1, sizeof(FILE_PATH_tF1)); 
	}
	hFile = Bfile_OpenFile_OS(pFile, READ);
	
	if(x1 > 40) x1 = 40;
	x1--;
	if(x2 > 40) x2 = 40;
	//x2--;
	
	char num[10];
    int j;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
	
	int countX1, countX2;
    unsigned long int pos = 0;
    for(countX1 = 0; countX1 < x1; countX1++){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	
    for(countX2 = 0; countX2 < x2; countX2++){
	    for(j = 0; j < 10; j++)
	    	num[j] = 0;
		j = 0;
		
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		
    		if(buffer != ';'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != ';');
	}
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}

void table_getWvalue(int x1, int x2, double *n){
	int hFile;
	unsigned short pFile[sizeof(FILE_PATH_tW)*2];
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tW, sizeof(FILE_PATH_tW)); 
	hFile = Bfile_OpenFile_OS(pFile, READ);
	
	if(x1 > 25) x1 = 25;
	x1--;
	if(x2 > 50) x2 = 50;
	x2--;
	
	char num[10];
    int j;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
	
	int countX1, countX2;
    unsigned long int pos = 0;
    for(countX1= 0; countX1 < x1; countX1++){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	
    for(countX2 = 0; countX2 < x2; countX2++){
	    for(j = 0; j < 10; j++)
	    	num[j] = 0;
		j = 0;
		
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		
    		if(buffer != ';'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != ';');
	}
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}
void table_getMvalue(int x, double a, double *n){
	if(x > 50) x = 50;
	x-=3;
	
	int div;
	if(a > 0.98)
		div = 9;
	else if(a > 0.973)
		div = 8;
	else if(a > 0.93)
		div = 7;
	else if(a > 0.75)
		div = 6;
	else if(a > 0.3)
		div = 5;
	else if(a > 0.08)
		div = 4;
	else if(a > 0.035)
		div = 3;
	else if(a > 0.015)
		div = 2;
	else
		div = 1;
		
		//printDouble(1, 1, (double)x, 5);
		//printDouble(1, 5, (double)div, 5);
	
	unsigned short pFile[sizeof(FILE_PATH_tM)*2]; // Make buffer
	int hFile;
    Bfile_StrToName_ncpy(pFile, (unsigned char*)FILE_PATH_tM, sizeof(FILE_PATH_tM)); 
	hFile = Bfile_OpenFile_OS(pFile, READ); // Get handle
    char num[10];
    int j;
    char buffer;
	if(hFile < 0){
		*n = -1;
		return;
	}
    
    int countX, countDiv;
    unsigned long int pos = 0;
    for(countX = 0; countX < x; countX++){
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
		}while(buffer != '|');
	}
	
	
    for(countDiv = 0; countDiv < div; countDiv++){
	    for(j = 0; j < 10; j++)
	    	num[j] = 0;
		j = 0;
		
    	do{
    		Bfile_ReadFile_OS(hFile,(char *) &buffer, 1, pos);
    		pos++;
    		
    		if(buffer != ';'){
				num[j] = buffer;
				j++;
			}
		}while(buffer != ';');
	}
	
	Bfile_CloseFile_OS(hFile);
	
		//int key;
		//printText(5,3, "CERRADO");
		//printText(5,4, (char *) &num);
		//GetKey(&key);
		
		
	stringRealToDouble((char *) &num, n);
}


