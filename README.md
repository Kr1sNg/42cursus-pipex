# pipex - Redirections and Pipes in UNIX 🚿

### 💡 Mandatory Part
The program pipex should mimic behaviours of the following shell command:
```bash
$> < filein cmd1 | cmd2 > fileout
```
and looks like this:
```bash
$> ./pipex filein cmd1 cmd2 fileout
```
All errors like: wrong commands, permission to files and etc, need to be handled.

### 🕯️ Bonus Part
The program needs to handle multiple pipes
```bash
$> < filein cmd1 | cmd2 | cmd3 | ... | cmdn > fileout

$> ./pipex filein cmd1 cmd2 cmd3 ... cmdn fileout
```
Support `<<` and `>>`, when instead of `file1` is `here_doc`.
```bash
$> cmd1 << LIMITER | cmd2 >> fileout

$> ./pipex here_doc LIMITER cmd1 cmd2 fileout
```

---
### 🐛 Issues and Bugs
Please feel free to create a new issue with its title and description on the `issues` page of this [42cursus-pipex](https://github.com/Kr1sNg/42cursus-pipex/) repository. If you have already found the solution to the problem, I would love to review your `pull request`!

---
### 📚 References
- https://www.rozmichelle.com/pipes-forks-dups/
- https://www.codequoi.com/en/pipe-an-inter-process-communication-method/
