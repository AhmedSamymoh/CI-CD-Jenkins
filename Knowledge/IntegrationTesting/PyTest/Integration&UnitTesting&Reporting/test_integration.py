import pytest
from binding import add, multiply

def test_integration():
    result = add(2, 3)
    result = multiply(result, 5)
    assert result == 20
