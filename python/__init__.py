"""
    In the end, it's not the years in your life that count. It's the life in your years.
    ~ Abraham Lincoln
"""
from .CircularList import CircularList
from .Queue import Queue
from .MatrixGraph import MatrixGraph, WeightedMatrixGraph
from .DictGraph import DictGraph, WeightedDictGraph
from .setup import install

__all__ = [
    "Queue",
    "CircularList"
    "MatrixGraph",
    "DictGraph",
    "WeightedDictGraph",
    "WeightedMatrixGraph",
]


if __name__ == "__main__":
    from sys import argv

    argv += ['install']
    install()
