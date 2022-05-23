#define CURRENT 1
#define PARENT 2

message m;

int my_getpid()
{
    if (m_in.m4_l1 == 1)
    {
        return mproc[who_p].mp_pid;
    }
    return mproc[mp->mp_parent].mp_pid;
}

int mygetpid(long integer)
{
}