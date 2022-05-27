## 功能说明 ##
1. 验证连续3次fork,最终能打印多少行“hello world”

## 程序分析 ##
1. 由f o r k创建的新进程被称为子进程（ child process）。该函数被调用一次，但返回两次。两次返回的区别是子进程的返回值是 0，而父进程的返回值则是新子进程的进程 I D。

2. 子进程和父进程**继续执行 f o r k之后**的指令，子进程是父进程的复制品。

3. 进程树示图：
![](https://img2022.cnblogs.com/blog/663740/202205/663740-20220509143729833-466036024.png)

4. 打印结果, 共8行，如下：
```
cjb@cjb-VirtualBox:~/.../linuxC/fork$ ./fork 
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
Hello world!
```