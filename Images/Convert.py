import subprocess
import os
from pathlib import Path

def Convert(filename):
    input_file = f'{filename}.mp4'
    output_file = f'{filename}.gif'
    
    print(f"Converting {input_file}")

    cmd = [
        "ffmpeg",
        "-i", input_file,
        "-vf", "fps=10,scale=320:-1:flags=lanczos",
        "-c:v", "gif",
        output_file
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)

    print("STDOUT:", result.stdout)
    print("STDERR:", result.stderr)

    if result.returncode != 0:
        print("ffmpeg failed.")



if __name__ == "__main__":
    mp4_files = list(Path('.').glob('*.mp4'))
    [Convert(f.stem) for f in mp4_files]