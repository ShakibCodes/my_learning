import subprocess

subprocess.run(
    ["ls", "non_existent_file"],
    check=True
)
