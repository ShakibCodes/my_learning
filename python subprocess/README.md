# Subprocess

The subprocess module allows Python to spawn new processes, connect to their input/output/error pipes, and obtain their return codes.

### features

- Run terminal/CLI commands from Python
- Automate system task
- Capture command output programmatically
- Control long-running processes
- Replace older modules like `os.system()`

## Functions
### subprocess.run()
Runs a command, waits for it to finish, and returns a `CompletedProcess` object.

```python 
subprocess.run(args, *, capture_output=False, check=False, text=False, shell=False)
```
---
### subprocess.Popen()
Starts a process without waiting for it to finish.

```python
subprocess.Popen(args, *, stdin=None, stdout=None, stderr=None, text=False)
```
---
### subprocess.call()
Runs a command and returns its exit code.
<br>

> [!NOTE]
> Does NOT capture output

```python
subprocess.call(args)
```
<br>

## Examples

### 1. Running a command

```python
import subprocess
subprocess.run(["cmd", "/c", "dir"])
```

### 2. Capturing result

```python
import subprocess

result = subprocess.run(
    ["cmd", "/c", "dir"],
    capture_output=True,
    text=True
)

print(result.stdout)
```


## Example project
[git commit and push](gitex.py)