"""
    In the end, it's not the years in your life that count. It's the life in your years.
    ~ Abraham Lincoln
"""
from CircularList import CircularList
from queue import Queue
from MatrixGraph import MatrixGraph, WeightedMatrixGraph
from DictGraph import DictGraph, WeightedDictGraph

__all__ = [
    "Queue",
    "CircularList"
    "MatrixGraph",
    "DictGraph",
    "WeightedDictGraph",
    "WeightedMatrixGraph"
]

def install():
    from distutils.core import setup
    setup(name="data_structures",
      version="1.0",
      description="Python implementations of various data-sturctures",
      author="hero24",
      package_dir={'hero24/data_structures':'.'},
      packages=["hero24/data_structures"]
      )

if __name__ == "__main__":
    from sys import argv
    argv += ['install']
    install()


