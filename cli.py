#!/usr/bin/env python3

# Author: VLN37 @ github

import subprocess
import sys
import pathlib
import shutil
from enum import Enum
from pathlib import Path

CWD = pathlib.Path.cwd()
BOILER_DIR = CWD / "boilerplate"
WIDTH = shutil.get_terminal_size().columns


class Commands(Enum):
    Help = 0
    Create = 1
    Run = 2

    @staticmethod
    def from_str(v):
        for c in Commands:
            if v.lower() == c.name.lower():
                return c
        return None


class Cli:
    def run(self):
        if not self._is_valid():
            self.instructions()
            sys.exit(1)
        if self.command == Commands.Help:
            self.instructions()
            sys.exit(0)
        if self.command == Commands.Create:
            self.create()
            self.questionable_makefile_edit()
        if self.command == Commands.Run:
            self.run_exercise()

    def instructions(self, error=None):
        if error:
            print(f"Error: {error}\n")
        commands = "\n".join([x.lower().center(WIDTH) for x in Commands._member_names_])
        stuff = []
        stuff.append(" PISCINE OBJECT CLI ".center(WIDTH, "#"))
        stuff.append("Streamlining your piscine experience.".center(WIDTH))
        stuff.append(" commands ".center(WIDTH, "#"))
        stuff.append(commands)
        stuff.append(" example ".center(WIDTH, "#"))
        stuff.append("./cli.py create encapsulation ex00".center(WIDTH))
        stuff.append("./cli.py run encapsulation ex00".center(WIDTH))

        print("\n".join(stuff))

    def create(self):
        list_dir, ex_dir = self.args
        list_dir = Path(CWD / list_dir)
        ex_dir = Path(list_dir / ex_dir)

        if ex_dir.exists():
            print("Your exercise folder already exists. Exiting...")
            sys.exit(1)
        if not list_dir.exists():
            list_dir.mkdir()
        shutil.copytree(BOILER_DIR, ex_dir, dirs_exist_ok=True)
        Path(ex_dir / "src/.placeholder").unlink()

    def run_exercise(self):
        list_dir, ex_dir = self.args
        full_path: Path = CWD / list_dir / ex_dir
        if not full_path.exists():
            print(f"{full_path}\nThe path does not exist. Exiting...")
            sys.exit(1)
        subprocess.run(["make", "-C", full_path, "run"])

    def questionable_makefile_edit(self):
        with open("./Makefile", "r") as file:
            lines = file.readlines()
        with open("./Makefile", "w") as file:
            start = False
            found = False
            do_once = True
            for line in lines:
                if not start:
                    if not line.startswith("FOLDERS"):
                        file.write(line)
                        continue
                    start = True
                if not line.endswith("\\\n") and not found:
                    found = True
                    file.write(f"{line.rstrip()} \\\n")
                    continue
                if found:
                    if do_once:
                        line = f"\t\t  {self.args[0]}/{self.args[1]}\n\n"
                    do_once = False
                file.write(line)

    def __init__(self, argv) -> None:
        self.argv = argv
        self.valid = None

    def _is_valid(self) -> bool:
        if self.valid is not None:
            return self.valid
        if len(self.argv) < 2:
            return False
        _, command, *args = self.argv
        self.command = Commands.from_str(command)
        self.args = args
        if not self.command:
            return False
        if self.command in [Commands.Create, Commands.Run]:
            if len(args) != 2:
                return False
        return True


if __name__ == "__main__":
    Cli(sys.argv).run()
