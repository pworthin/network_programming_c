#include <termios.h>

volatile sig_atomic_t shutdown_requested = 0;
struct termios temp;

void activator(int sigNum){
    (void)sigNum;
    shutdown_requested = 1;

}

void sentinel(void) {
    struct sigaction sa = {0};

    sa.sa_handler = activator;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;               // importantly: no SA_RESTART

    sigaction(SIGINT, &sa, NULL);
    io_config();
    terminal_guard();

}


void io_config(void){


    struct termios old_term, new_term;
    temp = old_term;
    if (tcgetattr(STDIN_FILENO, &old_term) == 0) {
        new_term = old_term;
        new_term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }
}

void terminal_guard(void) {

    tcsetattr(STDIN_FILENO, TCSANOW, &temp);
}