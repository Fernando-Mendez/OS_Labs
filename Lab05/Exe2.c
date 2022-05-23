/*===========================================================================*
 *				pick_proc				     *
 *===========================================================================*/
static struct proc *
pick_proc()
{
    //  /* Decide who to run now.  A new process is selected and returned.
    //   * When a billable process is selected, record it in 'bill_ptr', so that the
    //   * clock task can tell who to bill for system time.
    //   *
    //   * This function always uses the run queues of the local cpu!
    //   */
    //   register struct proc *rp;                  /* process to run */
    //   struct proc **rdy_head;
    //   int q;                             /* iterate over queues */

    //   /* Check each of the scheduling queues for ready processes. The number of
    //     * queues is defined in proc.h, and priorities are set in the task table.
    //     * If there are no processes ready to run, return NULL.
    //     */
    //   rdy_head = get_cpulocal_var(run_q_head);
    //   for (q=0; q < NR_SCHED_QUEUES; q++) {
    //      if(!(rp = rdy_head[q])) {
    //              TRACE(VF_PICKPROC, printf("cpu %d queue %d empty\n", cpuid, q););
    //              continue;
    //      }
    struct proc *rp;
    rp = rdy_head[q];
    /*************** your lottery scheduling algorithm below ***************/

    int sum = 0;
    int winnerTicket = rand() % total_tckts;
    while (rp->p_nextready != NULL)
    {
        sum += rp->tickets;
        if (sum >= winnerTicket && rp->tickets > 10)
        {
            if (cont_wins < 2)
            {
                cont_wins++;
                total_tckts -= rp->tickets;
                return rp;
            }
            else
            {
                struct proc *lowestTicket = rp;
                struct proc *prev = rp;
                cont_wins = 0;
                while (lowestTicket->p_nextready != NULL)
                {
                    prev = lowestTicket;
                    lowestTicket = lowestTicket->p_nextready;
                }
                if (lowestTicket->tickets > 10)
                {
                    cont_wins++;
                    total_tckts -= lowestTicket->tickets;
                    return lowestTicket;
                }
                sum += lowestTicket->tickets;
                prev->p_nextready = NULL;
                lowestTicket = NULL;
            }
        }
        rp = rp->p_nextready;
    }
    total_tckts -= rp->tickets;

    /*************** your lottery scheduling algorithm  above ***************/

    //      assert(proc_is_runnable(rp));
    //      if (priv(rp)->s_flags & BILLABLE)
    //              get_cpulocal_var(bill_ptr) = rp; /* bill for system time */
    return rp;
}