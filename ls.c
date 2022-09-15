#include <unistd.h>

int main()
{
  char * command = "ls";
  execvp( command, &command );
  return 0;
}
