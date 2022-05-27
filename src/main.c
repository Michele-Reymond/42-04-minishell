//compilation:
// gcc readline.c -L/usr/local/lib -I/usr/local/include -lreadline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char** argv) 
{
  printf("Welcome! You can exit by pressing Ctrl+C at any time...\n");

  //if (argc > 1 && ((argv[1]) == "-d"))
  {
    // By default readline does filename completion. With -d, we disable this
    // by asking readline to just insert the TAB character itself.
    //rl_bind_key('\t', rl_insert);
  }

  char* buf;
  while ((buf = readline("🌸 >> ")) != NULL) 
  {
    if (strlen(buf) > 0) 
    {
      add_history(buf);
      ms-bultins(buf);
    }
        }
    else if (!strcmp(buf, "exit")) 
        {
            break;
        }
    printf("[%s]\n", buf);

    // readline malloc's a new buffer every time.
    free(buf);
  }

  return (0);
}