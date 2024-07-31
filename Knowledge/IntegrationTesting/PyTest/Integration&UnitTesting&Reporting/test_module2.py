import pytest
from binding import multiply

def test_multiply():
    assert multiply(2, 3) == 6
    assert multiply(-1, -2) == 2
    assert multiply(0, 5) == 0
