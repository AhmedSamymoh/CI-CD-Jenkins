import ctypes

# Load the shared libraries
module1 = ctypes.CDLL("C:\\Users\\study\\OneDrive\\Desktop\\pyTest\\IntegrationTest\\module1.so")
module2 = ctypes.CDLL("C:\\Users\\study\\OneDrive\\Desktop\\pyTest\\IntegrationTest\\module2.so")

# defining the arguments and function return types for ADD
module1.add.argtypes = (ctypes.c_int, ctypes.c_int)
module1.add.restype = ctypes.c_int

# defining the arguments and function return types for MULLLLLLLLL
module2.multiply.argtypes = (ctypes.c_int, ctypes.c_int)
module2.multiply.restype = ctypes.c_int




# define to be more readable and ease to use
def add(a, b):
    return module1.add(a, b)


def multiply(a, b):
    return module2.multiply(a, b)
