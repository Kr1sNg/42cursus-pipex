# 42cursus-pipex
Redirections and Pipes in UNIX

## Mandatory Part
The program pipex should repeat the behaviour of the next shell command:
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like this:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
All errors like: wrong commands, permission to files and etc, need be handle.

## Bonus Part
Program need handle multiple pipes
```bash
$> < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2

$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Support `<<` and `>>`, when instead of `file1` is `here_doc`.
```bash
$> cmd1 << LIMITER | cmd2 >> file2

$> ./pipex here_doc LIMITER cmd1 cmd2 file2
```
#### References
- https://www.rozmichelle.com/pipes-forks-dups/
- https://www.codequoi.com/en/pipe-an-inter-process-communication-method/

