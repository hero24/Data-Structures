"""
    In the end, it's not the years in your life that count. It's the life in your years.
    ~ Abraham Lincoln
"""
from CircularList import CircularList
from queue import Queue
from GraphMatrix import GraphMatrix

__all__ = [
    "Queue",
    "CircularList"
    "GraphMatrix"
]

if __name__ == "__main__":
    from distutils.core import setup
    from sys import argv
    argv += ['install']

    setup(name="data_structures",
      version="0.1",
      description="Python implementations of various data-sturctures",
      author="hero24",
      package_dir={'hero24/data_structures':'.'},
      packages=["hero24/data_structures"]
      )

