#include <stdio.h>
#include <time.h>
#include <string.h>
#include "BibliotecaData.h"
char DataEmprestimoDevolucao[11];

int main() {
    int day1, month1, year1, day2, month2, year2;
    
    

/*  printf("Digite a primeira data (formato: DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day1, &month1, &year1);
*/


/*	day2 = 01;
	month2 = 01;
	year2 = 2024;
*/	

	strcpy(DataEmprestimoDevolucao, "15/05/2024");

// Extrai os valores de dia, mês e ano da string DataEmprestimoDevolucao

	sscanf(DataEmprestimoDevolucao, "%d/%d/%d", &day1, &month1, &year1);
	
	
	

/*  printf("Digite a segunda data (formato: DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day2, &month2, &year2);
*/	


	time_t now;
	struct tm *local_time;

	time(&now);
	local_time = localtime(&now);
	

	day2 = local_time->tm_mday;
	month2 = local_time->tm_mon + 1;
	year2 = local_time->tm_year + 1900;
	
    DifData(day1, month1, year1, day2, month2, year2);

    return 0;
}
