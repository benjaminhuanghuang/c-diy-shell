
## 一个 shell 在它的生命周期中主要做三件事。
- 初始化 ：在这一步中，shell 一般会加载并执行它的配置文件。这些配置会改变 shell 的行为。
- 解释执行 ：接着，shell 会从标准输入（可能是交互式输入，也可能是一个文件）读取命令，并执行这些命令。
- 终止 ：当命令全部执行完毕，shell 会执行关闭命令，释放所有内存，然后终止。

```
int main(int argc, char **argv)
{
  // 如果有配置文件，则加载

  // 运行命令循环
  lsh_loop();

  // 做一些关闭和清理工作
  return EXIT_SUCCESS;
}
```


## Main loop
main loop 要做的三件事：
- 读取 ：从标准输入读取一个命令。
- 分析 ：将命令字符串分割为程序名和参数。
- 执行 ：运行分析后的命令。
```
void lsh_loop(void)
{
  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);
  } while (status);
}
```

## Read
从标准输入读取一行听起来很简单，但用 C 语言做起来可能有一定难度。因为法预先知道用户会在 shell 中键入多长的文本。因此不能简单地分配一块空间，来装下用户的输入，而应该先暂时分配一定长度的空间，当确实装不下用户的输入时，再重新分配更多的空间。这是 C 语言中的一个常见策略，



## Parse



