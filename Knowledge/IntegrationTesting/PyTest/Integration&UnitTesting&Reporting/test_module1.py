import pytest
from binding import add

def test_add():
    assert add(1, 2) == 3
    assert add(-1, -2) == -3
    assert add(0, 0) == 0
