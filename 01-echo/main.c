#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSH_READ_LINE_BUFSIZE 1024
#define LSH_TOKEN_BUFSIZE 64
#define LSH_TOKEN_DELIM " \t\r\n\a"

char *lsh_read_line(void)
{
  int bufsize = LSH_READ_LINE_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // 读一个字符
    c = getchar();

    // 如果我们到达了 EOF, 就将其替换为 '\0' 并返回。
    // EOF 是一个整型值而不是字符型值。如果将它的值作为判断条件，c 需要使用 int 类型
    if (c == EOF || c == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = c;
    }
    position++;

    // 如果我们超出了 buffer 的大小，则重新分配。
    if (position >= bufsize)
    {
      bufsize += LSH_READ_LINE_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char *lsh_read_line_2(void)
{
  char *line = NULL;
  getline(&line, 0, stdin);
  return line;
}

char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOKEN_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;
  if (!tokens)
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOKEN_DELIM);
  while (token != NULL)
  {
    tokens[position] = token;
    position++;

    if (position >= bufsize)
    {
      bufsize += LSH_TOKEN_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOKEN_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int lsh_execute(char **args)
{
  if (args[0] == NULL)
  {
    // An empty command was entered.
    return 1;
  }

  printf("%s\n", args[0]);

  return 1;
}

void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do
  {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  // 如果有配置文件，则加载。

  // 运行命令循环
  lsh_loop();

  // 做一些关闭和清理工作。

  return EXIT_SUCCESS; // stdlib
}
