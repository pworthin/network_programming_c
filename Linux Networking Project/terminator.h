

#ifndef SNIFFER_PROJECT_TERMINATOR_H
#define SNIFFER_PROJECT_TERMINATOR_H

void sentinel(void);
void tstate_return(void);
extern volatile sig_atomic_t shutdown_requested;

#endif //SNIFFER_PROJECT_TERMINATOR_H