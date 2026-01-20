# MAKEFLAGS += -s

DYNAMIC_LIB_NAME := arr
ALL_LIB_NAME := $(STATIC_LIB_NAME) $(DYNAMIC_LIB_NAME) $(DYNAMIC_LOAD_LIB_NAME)
LIBS := $(patsubst %, ./lib/lib%.a, $(STATIC_LIB_NAME)) $(patsubst %, ./lib/lib%.so, $(DYNAMIC_LIB_NAME) $(DYNAMIC_LOAD_LIB_NAME)) 


CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
# CFLAGS := -Wall -Werror -Wextra -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
LDFLAGS := -lm -ldl -L./lib $(addprefix -l, $(STATIC_LIB_NAME) $(DYNAMIC_LIB_NAME)) -Wl,-rpath,'./lib'


SRCS := $(wildcard ./src/*.c)
SRCS := $(filter-out $(patsubst %, ./src/%.c, $(ALL_LIB_NAME)), $(SRCS))
OBJS := $(patsubst ./src/%.c, ./out/%.o, $(SRCS))
UNIT_OBJS := $(patsubst ./unit_tests/%.c, ./out/%.o, $(wildcard ./unit_tests/*.c)) $(filter-out ./out/main.o, $(OBJS))

DEPS := $(patsubst ./%.o, ./%.d, $(OBJS) $(UNIT_OBJS)) $(patsubst %, ./out/%.d, $(ALL_LIB_NAME)) 
NODEPS := clean

.PHONY: clean release debug asan ubsan msan func func_tests unit_tests.exe test dlib

### СБОРКИ ПРОГРАММЫ
# сборка основной программы
app.exe: $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
# сборка модульных тестов
unit_tests.exe: LDFLAGS += -lcheck -lpthread
unit_tests.exe: $(UNIT_OBJS) $(LIBS)
	echo $(UNIT_OBJS)
	$(CC) $(UNIT_OBJS) $(LDFLAGS) -o $@

# релизная сборка
release: CFLAGS += -g0
release: app.exe
# сборка для дебага
debug: CFLAGS += -g3
debug: app.exe


# Санитайзер адрессов
asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan: LDFLAGS += -fsanitize=address
asan: debug
# Сантизайзер неопределенного поведения
ubsan: CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
ubsan: LDFLAGS += -fsanitize=undefined
ubsan: debug
# Сантизайзер памяти
msan: CFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer
msan: LDFLAGS += -fsanitize=memory -fPIE -pie
msan: debug

# Сборка для проверки покрытия тестов
gcov: CFLAGS += -coverage
gcov: LDFLAGS += -coverage
gcov: app.exe


### СБОРКИ БИБЛИОТЕК
dlib: ./lib/libarr.so
# динамические встраиваемые	
./out/arr.o: ./src/arr.c
	mkdir -p out
	$(CC) $(CFLAGS) -fPIC -MMD -MP -c $< -o $@
./lib/libarr.so: ./out/arr.o
	mkdir -p lib
	$(CC) -o $@ -shared $<


### ЗАПУСК ФУНКЦИОНАЛЬНЫХ ТЕСТОВ
# Запуск без санитайзеров
func: release
	-./func_tests/scripts/func_tests.sh
# Все санитайзеры
func_san: func_asan func_ubsan func_msan
# Адресс санитайзер
func_asan: asan
	@echo "=== Running ASan tests ==="
	@-./func_tests/scripts/func_tests.sh
# Санитайзер неопределенного поведения
func_ubsan: ubsan
	@echo "=== Running UBSan tests ==="
	@-./func_tests/scripts/func_tests.sh
# Санитайзер памяти
func_msan: msan
	@echo "=== Running MSan tests ==="
	@-./func_tests/scripts/func_tests.sh


### Запуск модульных тестов
unit: unit_tests.exe
	-./unit_tests.exe

# Объектные файлы
./out/%.o: ./src/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
./out/%.o: ./unit_tests/%.c
	mkdir -p out
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	-include $(DEPS)
endif



# очиста генерируемых файлов
clean:
	@echo $(SRCS)
# 	rm -fr *.o *.exe *.d *.txt *.bin *.gcno *.gcda *.gcov
	rm -rf out
	rm -f *.exe
	mkdir -p out
clean_lib:
	rm -r lib
clean_all: clean clean_lib

# TODO


# # покрытие тестов
# collect_coverage

# # Сборка для проверки покрытия тестов
# build_gcov
