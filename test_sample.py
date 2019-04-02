import pytest

def func(x):
	return x + 1
	
def test_answer():
	assert func(3) == 5

def test_foo():
	assert func(3) == 4


def funcThrows():
	raise SystemExit(1)
	
def test_funcThrowTest():
	with pytest.raises(SystemExit):
		funcThrows()
