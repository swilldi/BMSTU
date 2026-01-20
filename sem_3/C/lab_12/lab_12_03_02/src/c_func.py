import ctypes

lib = ctypes.CDLL("./lib/libarr.so")

# void arr_fill_prime_num(int *arr, int n);
_fill_prime_num = lib.arr_fill_prime_num
_fill_prime_num.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_fill_prime_num.restype = None

# int arr_add_after_even(int *src, int src_n, int *dst, int *dst_n, int fill_num);
_add_afret_even = lib.arr_add_after_even
_add_afret_even.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_add_afret_even.restype = ctypes.c_int


# === заполнение массива простыми числами ===
def arr_fill_prime_num(n: list[int]) -> list[int]:     
     src = (ctypes.c_int * n)()
     _fill_prime_num(src, n)
     return list(src)

# === Добавление после каждого четного переданное число ===
# Выделение памяти с запасом
def arr_add_after_even_1(arr: list[int], fill_num: int) -> list[int]:
    src_len = len(arr)
    src = (ctypes.c_int * src_len)(*arr)
    
    dst_len = ctypes.c_int(src_len * 2)
    dst = (ctypes.c_int * dst_len.value)()
    
    _add_afret_even(src, src_len, dst, dst_len, fill_num)
    return list(dst)

# Два запуска функции: определить длину выходного массива -> заполнить массив
def arr_add_after_even_2(arr: list[int], fill_num):
    src_len = len(arr)
    src = (ctypes.c_int * src_len)(*arr)
    
    dst_len = ctypes.c_int(0)
    _add_afret_even(src, src_len, None, dst_len, fill_num)
    dst = (ctypes.c_int * dst_len.value)()
    
    _add_afret_even(src, src_len, dst, dst_len, fill_num)
    return list(dst)

