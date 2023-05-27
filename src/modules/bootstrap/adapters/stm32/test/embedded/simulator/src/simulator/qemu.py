import os
import sys
import threading
import subprocess
import time
from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Iterable, Optional, Tuple
import argparse


class StoppableThreadBase(ABC):
    func_args: Optional[Iterable] = None
    keep_alive: bool = True
    thread: threading.Thread

    def run(self):
        self.start()
        while self.keep_alive:
            pass
        self.stop()

    @abstractmethod
    def thread_target(self):
        raise NotImplementedError

    @abstractmethod
    def start(self):
        raise NotImplementedError

    @abstractmethod
    def stop(self):
        raise NotImplementedError


class StoppableSubprocessThread(StoppableThreadBase):
    process: subprocess.Popen[str] = None

    def __init__(
        self,
        subprocess_args: Tuple[str, ...],
        timeout: Optional[float] = None,
        shell: bool = False,
    ):
        self.args = subprocess_args
        self.timeout = timeout
        self.thread = threading.Thread(target=self.thread_target)
        self.shell = shell
        if self.timeout:
            self.keep_alive = False

    def thread_target(self):
        stdout = None if self.shell else subprocess.PIPE
        self.process = subprocess.Popen(self.args, stdout=stdout, shell=self.shell)
        print(f"Running {' '.join(self.args)}. PID: {self.process.pid}")

        if self.keep_alive:
            self.process.wait()

    def start(self):
        self.thread.start()

    def stop(self):
        self.thread.join(self.timeout)
        if self.thread.is_alive():
            self.process.wait(self.timeout)


@dataclass
class ModContext:
    delay: float = None
    timeout: float = None
    shell: bool = False
    disable: bool = False
    script: str = ""

@dataclass
class Context:
    qemu: ModContext
    gdb: ModContext


def namespace_to_context(ns: argparse.Namespace) -> Context:
    def gen():
        for attr in ("qemu", "gdb"):
            yield attr, ModContext(
                delay=getattr(ns, f"delay_{attr[0]}"),
                timeout=getattr(ns, f"timeout_{attr[0]}"),
                shell=getattr(ns, f"shell_{attr[0]}"),
                disable=getattr(ns, f"no_{attr}"),
            )
    return Context(**dict(gen()))


def parse() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Runs QEMU and GDB scripts.")
    parser.add_argument(
        "-dG",
        "--delay-g",
        type=int,
        help="Delay starting gdb by given ms",
        default=None,
    )
    parser.add_argument(
        "-dQ",
        "--delay-q",
        type=int,
        help="Delay starting qemu by given ms",
        default=None,
    )
    parser.add_argument(
        "-tG", "--timeout-g", type=int, help="GDB Timeout in s", default=None
    )
    parser.add_argument(
        "-tQ", "--timeout-q", type=int, help="QEMU Timeout in s", default=None
    )
    parser.add_argument(
        "-sG", "--shell-g", type=bool, help="Run GDB in shell", default=False
    )
    parser.add_argument(
        "-sQ", "--shell-q", type=bool, help="Run QEMU in shell", default=True
    )
    parser.add_argument(
        "-nG", "--no-gdb", type=bool, help="Disable GDB ", default=False
    )
    parser.add_argument(
        "-nQ", "--no-qemu", type=bool, help="Disable GDB ", default=False
    )
    return parser.parse_args()


def start_thread(ctx: ModContext):
    if not ctx.disable:
        if ctx.timeout is not None:
            time.sleep(ctx.timeout / 1000)
        t = StoppableSubprocessThread(
            ("/bin/zsh", ctx.script),
            timeout=ctx.timeout,
            shell=ctx.shell,
        )
        t.start()
        return t

def main():
    ctx = namespace_to_context(parse())
    ctx.qemu.script = "scripts/qemu_runner.sh"
    ctx.gdb.script = "./scripts/gdb_runner.sh"
    threads = []
    for thread in (ctx.qemu, ctx.gdb):
        threads.append(start_thread(thread))

    for thread in threads:
        thread.thread.join()


if __name__ == "__main__":
    main()
