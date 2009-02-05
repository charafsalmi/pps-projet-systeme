struct sigaction sigCreve;

sigCreve.sa_handler=nomdetafonctionvoid;
sigCreve.sa_flags=0;
sigCreve.sa_restorer=NULL;

sigaction(SIGUSR1,&sigCreve,NULL);
