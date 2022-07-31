# c-logs

## Instruction

### Start
Returned `LOGS *`, `NULL` - in case of an error.

---
**full_start**

```c
LOGS *full_start(const char *file_name, enum Level level, bool w_time, bool is_clear_log_file,  bool open_file_every_time)
```
* `level` - logging level
* `is_clear_log_file` - clear the file before use
* `open_file_every_time` - reopen the file every time logging (it will slow down the program, but data is more likely to be saved during a crash)
* `w_time` - display the time every time

Example:
```c
LOGS *logs = full_start("logs.txt", verbose, false, true);
```

---
**quick_start**

```c
LOGS *quick_start(const char *file_name)
```

By default:
* `level` - `warning`
* `is_clear_log_file` - `false`
* `open_file_every_time` - `true`

Example:
```c
LOGS *logs = quick_start("logs.txt");
```

---

### CLOSE
***Do not forget to close the logs!***, parameter - pointer to the LOGS structure (`LOGS *`), `quick_start` or `full_start` result:
`lclose(logs);`

### Logging levels
* `off` - the lowest, is logged nothing
* `critical_error`
* `error`
* `warning`
* `info`
* `verbose` - the highest, everything is logged

### Logging

---
`line` - print the line number (use `__LINE__`)\
`w_time` - do I need to print the time

---

Without line and time:
```c
bool flog(LOGS *logs, const enum Level level, const char *str_log, ...)
```
---

With line, without time:
```c
bool flog_l(LOGS *logs, const size_t line, const enum Level level, const char *str_log, ...)
```
---

With time, without line:
```c
bool flog_t(LOGS *logs, bool w_time, const enum Level level, const char *str_log, ...)
```
---

With time and line:
```c
bool flog_tl(LOGS *logs, bool w_time, const size_t line, const enum Level level, const char *str_log, ...)
```

---

```c
bool vflog(LOGS *logs, const size_t line, const enum Level level, const char *str_log, va_list args)
```
```c
bool vflog_t(LOGS *logs, bool w_time, const size_t line, const enum Level level, const char *str_log, va_list args)
```

---

Prints to the logging file and error stream
```c
int print_err(LOGS *logs, const enum Level level, const size_t line, const char *str_err, ...)
```

---

## Example

```c
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
```

output (`logs.txt`):

```
Thu Jul 28 15:29:09 2022
in line - 6
START PROGRAM!

Thu Jul 28 15:29:09 2022
in line - 10
Array:
1: -1391591424
2: 32759
3: 0
4: 1
5: 146798176
6: 40
7: -1391582488
8: 32759
9: 1390220240
10: 495

Thu Jul 28 15:29:09 2022
in line - 18
END PROGRAM!
```
