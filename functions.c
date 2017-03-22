#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
//#include <cjson/cJSON.h>
#include "definitions.h"

void
init_curses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
}

void
quote(char* str)
{
    mvprintw(getmaxy(stdscr) / 3.5, getmaxx(stdscr) / 2, str);
}

/*size_t
write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct mem_struct *mem = (struct mem_struct*) userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        /* out of memory */
        puts("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), buffer, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}*/