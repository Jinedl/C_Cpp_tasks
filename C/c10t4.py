#! /usr/bin/python3
from functools import reduce; from operator import mul; import sys; print(reduce(mul, [int(x) for x in sys.argv if x.isdigit()]))
