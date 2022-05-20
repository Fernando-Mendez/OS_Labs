void printString(char *c)
{
    printf("%c", *c);
}

void generate_SIGSEGV()
{
    char *c = NULL;
    printString((char *)c);
}

void generate_SIGFPE()
{
    int a = 1, b = 0;
    printf("%d / %d = %d", a, b, a / b);
}