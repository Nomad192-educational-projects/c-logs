#include "logs.h"

int main(void) {
    LOGS *my_log = quick_start("logs.txt");
    flog_l(my_log, __LINE__, error, "START PROGRAM!\n\n");


    int arr[10];
    flog_l(my_log, __LINE__, critical_error, "Array:\n");

    size_t i = 0;
    while (i < 10) {
        flog_t(my_log, false, critical_error, "%d: %d\n", i + 1, arr[i]);
        i++;
    }
    flog_t(my_log, false, critical_error, "\n");


    flog_l(my_log, __LINE__, error, "END PROGRAM!\n\n");
    lclose(my_log);

    return 0;
}