

void DifData(int day1, int month1, int year1, int day2, int month2, int year2) {
    struct tm tm1, tm2;
    time_t time1, time2;
    double elapsed_days;

    // Preenche as estruturas tm com os valores fornecidos pelo usuário
    tm1.tm_mday = day1;
    tm1.tm_mon = month1 - 1; // Mês é base 0 (janeiro = 0, fevereiro = 1, etc.)
    tm1.tm_year = year1 - 1900; // Ano é base 1900

    tm2.tm_mday = day2;
    tm2.tm_mon = month2 - 1;
    tm2.tm_year = year2 - 1900;

    // Ajusta os valores para o formato esperado pela função mktime
    tm1.tm_hour = 0;
    tm1.tm_min = 0;
    tm1.tm_sec = 0;

    tm2.tm_hour = 23;
    tm2.tm_min = 59;
    tm2.tm_sec = 59;

    // Converte as estruturas tm para time_t
    time1 = mktime(&tm1);
    time2 = mktime(&tm2);

    // Calcula a diferença em segundos
    elapsed_days = difftime(time2, time1) / (60 * 60 * 24);

    printf("Tempo decorrido: %.0lf dias\n", elapsed_days);
}