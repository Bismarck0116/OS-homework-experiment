#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
pid_t pid = fork();
if (pid == 0)
{
int res = execl(“/usr/bin/vi”,”vi”,NULL);
if(res == 1)
perror(“execl”);
exit(0);
}
else if (pid > 0)
{
while(1);
}

return 0;
}