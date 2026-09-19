

#ifndef SNIFFER_PROJECT_TERMINATOR_H
#define SNIFFER_PROJECT_TERMINATOR_H

void sentinel(void);
void terminal_guard(void);
volatile sig_atomic_t shutdown_requested = 0;

#endif //SNIFFER_PROJECT_TERMINATOR_H