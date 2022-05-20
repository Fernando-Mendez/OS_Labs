/* Example of use of fork system call */ #include #include #include #include main()
{
    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed!\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        printf("Child process (%d) belongs to parent (%d)\n", getpid(), getppid());
        execlp("/bin/ps", "ps", NULL);
        printf("Still around...\n");
    }
    else
    {
        int childStatus;
        printf("Parent's (%d) child (%d)\n", getppid(), pid);
        waitpid(pid, &childStatus, 0);
        printf("Child (%d) finished with status ... %d", pid, childStatus);
        exit(0);
    }
}