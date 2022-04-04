#ifndef __TEST_DAEMON_H__
#define __TEST_DAEMON_H__

#include "../header.h"
#include "fcntl.h"

void start_daemon()
{
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
    int count = 0;
    while(count < 10)
    {
        sleep(1);
        count++;
    }
}

TEST(Test_Base,test_daemon)
{
    start_daemon();
}

#endif // __TEST_DAEMON_H__