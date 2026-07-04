#include <signals.h>

#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <globals.h>

static void handle_signals(int sig) {
    gRunning = 0;
}

void setup_sig_handlers(void) {
    struct sigaction sa = {0};
    
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_signals;
    sa.sa_flags = 0;

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    
    signal(SIGPIPE, SIG_IGN);
}