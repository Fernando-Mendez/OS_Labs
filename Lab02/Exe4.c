// Add handler functions here
void SIGINT_handler(int);
void SIGQUIT_handler(int);
void SIGTERM_handler(int);
void SIGFPE_handler(int);
void SIGSEGV_handler(int);
void SIGILL_handler(int);

void setup_signal_handlers()
{
    // Setup handlers here
    signal(SIGINT, SIGINT_handler);
    signal(SIGQUIT, SIGQUIT_handler);
    signal(SIGTERM, SIGTERM_handler);
    signal(SIGFPE, SIGFPE_handler);
    signal(SIGSEGV, SIGSEGV_handler);
    signal(SIGILL, SIGILL_handler);
}

void SIGINT_handler(int sig)
{
    printf("Received signal SIGINT!!!");
}
void SIGQUIT_handler(int sig)
{
    printf("Received signal SIGQUIT!!!");
}
void SIGTERM_handler(int sig)
{
    printf("Received signal SIGTERM!!!");
}
void SIGFPE_handler(int sig)
{
    printf("Received signal SIGFPE!!!");
}
void SIGSEGV_handler(int sig)
{
    printf("Received signal SIGSEGV!!!");
}
void SIGILL_handler(int sig)
{
    printf("Received signal SIGILL!!!");
}