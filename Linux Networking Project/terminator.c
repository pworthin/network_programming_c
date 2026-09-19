#include <signal.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>

#include "terminator.h"

/* Set by SIGINT handler to request a clean server shutdown. */
volatile sig_atomic_t shutdown_requested = 0;

/* Stores original terminal settings so they can be restored on exit. */
struct termios temp;

static void io_config(void);

/* SIGINT handler: set shutdown flag instead of exiting inside the handler. */
void activator(int sigNum){
    (void)sigNum;
    shutdown_requested = 1;

}

/* Install SIGINT handler and configure terminal behavior. */
void sentinel(void) {
    struct sigaction sa = {0};

    sa.sa_handler = activator;
    sigemptyset(&sa.sa_mask);
    /* No SA_RESTART: allows SIGINT to interrupt blocking accept(). */
    sa.sa_flags = 0;               // importantly: no SA_RESTART

    sigaction(SIGINT, &sa, NULL);
    io_config();


}

/* Save terminal settings and suppress the "^C" echo from Ctrl+C. */
static void io_config(void){


    struct termios new_term;

    if (tcgetattr(STDIN_FILENO, &temp) == 0) {
        new_term = temp;
        new_term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    }
}
/* Restore terminal to the state it was in before the program started. */
void tstate_return(void) {

    tcsetattr(STDIN_FILENO, TCSANOW, &temp);
}