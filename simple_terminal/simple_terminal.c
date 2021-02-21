/**
 * Author: Enmanuel Parache
 * Unlicensed
 */

#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "utils.h"

void ask_name_and_salute(void);
void process_command(void);
void print_help(void);

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        // ask_name_and_salute();
        process_command();
    }
    return 0;
}

void ask_name_and_salute(void) {
    char name[MAX_NAME_SZ];
    printf("What's your name? ");
    scanf("%s", name);
    clear_line();
    printf("Hello, %s! ", name);
    sleep_ms(2000);
    clear_line();
    return;
}

void process_command(void) {
    char command[5];
    int result = 0;

    printf("Please insert a command > ");
    scanf("%s", command);
    clear_line();

    for (char *p = command; *p; ++p) *p = tolower(*p); // lowercase command
    if (equal_str(command, "off")) {
        result = 0;
    }
    else if (equal_str(command, "on")) {
        result = 1;
    }
    else if (equal_str(command, "hello")) {
        result = 2;
    }
    else if (equal_str(command, "help")) {
        print_help();
    }
    else {
        result = -1;
    }

    switch (result)
    {
    case 0:
        gpio_put(LED_PIN, 0);
        break;
    case 1:
        gpio_put(LED_PIN, 1);
        break;
    case 2:
        ask_name_and_salute();
        break;
    default:
        printf("Error: command %s is not supported", command);
        sleep_ms(2000);
        clear_line();
        break;
    }
    return;
}

void print_help(void) {
    printf("\nCommand\tDescription\n");
    printf("\n");
    printf("on\tturn pico led on\n");
    printf("off\tturn pico's led off\n");
    printf("help\tasks your name and salute\n");
    printf("\nNote:\tall commands are case insensitive :)");
    printf("\n");
    return;
}