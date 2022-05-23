int do_mycall()
{
    printf("Hola! El número es: %ld\n", m_in.m4_l1);
    return 0;
}

int mycall(long integer)
{
    message m;
    m.m_type = M4;
    m.m4_l1 = integer;
    return _syscall(PM_PROC_NR, MYCALL, &m);
}