CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wpedantic -std=c99 -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
LDFLAGS := -lm
OBJS := $(patsubst ./src/%.c, ./out/%.o, $(wildcard ./src/*.c))

.PHONY: clean release debug asan ubsan msan func func_tests

### СБОРКИ ПРОГРАММЫ
# сборка основной программы
app.exe: $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

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


# Объектные файлы
./out/%.o: ./src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependens файлы, с зависимостями
NODEPS := clean test

./out/%.d: ./src/%.c
	$(CC) -MM $< > $@

SRCS := $(wildcard ./out/*.d)
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	include $(SRCS)
endif

# очиста генерируемых файлов
clean:
# 	rm -fr *.o *.exe *.d *.txt *.bin *.gcno *.gcda *.gcov
	rm -rf out
	mkdir -p out
	

# TODO
# # сборка модульных тестов
# unit_tests.exe

# # запуск модульных тестов
# unit

# # покрытие тестов
# collect_coverage

# # Сборка для проверки покрытия тестов
# build_gcov
