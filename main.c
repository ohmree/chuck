#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <cjson/cJSON.h>
//#include <curl/curl.h>
#include <neon/ne_session.h>
#include "definitions.h"
int main()
{
    CURL* curl_handle;
    CURLcode res;

    struct mem_struct chunk;

    chunk.memory = malloc(1);
    chunk.size   = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* specify url*/
    curl_easy_setopt(curl_handle, CURLOPT_URL, "https://api.chucknorris.io/jokes/random");

    /* send all data to write_data() */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* pass our data - 'chunk' - to the write_data() callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &chunk);

    /* provide a user agent */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* init ncurses */
    //init_curses();
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
    nodelay(stdscr, 0);

    /* prompt the user */
    //puts("Press enter to display a joke\n");
for(;;) {
    /* get the json data */
    res = curl_easy_perform(curl_handle);

    /* check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",\
        curl_easy_strerror(res));
    } else {
        /*
         * Now, our chunk.memory points to a memory block that is chunk.size
         * bytes big and contains the remote file.
         *
         * Do something nice with it!
         */

        cJSON* root   = cJSON_Parse((char *) chunk.memory);
        char*  joke   = cJSON_GetObjectItem(root, "value")->valuestring;
        printw("Here's a joke:\n %s\n", joke);
        cJSON_Delete(root);
        getch();
    }
}
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);

    /* cleanup libcurl */
    curl_global_cleanup();

    /* cleanup stdscr */
    endwin();

    return EXIT_SUCCESS;
}
