#!/usr/bin/env python3
# Генератор 100 строк (слов) с МАКСИМАЛЬНЫМИ коллизиями для полиномиального хэша:
# все слова попадают в ОДИН индекс: poly_hash(word) % TABLE_LEN == TARGET_BUCKET

from pathlib import Path
import random
import string

# ---------------- НАСТРОЙКИ ----------------
TABLE_LEN = 21          # длина хеш-таблицы (ИМЕННО len массива, на который ты берёшь %)
TARGET_BUCKET = 0        # в какую ячейку "загонять" все слова
NEEDED = 20             # сколько слов нужно

# Полиномиальный хэш: выбери вариант, который у тебя в C

P = 31                   # основание (часто 31/53)
MOD = 1_000_000_007       # модуль (если у тебя есть модуль). Если нет — не используется.

# 1) Вариант: h = (h*P + ord(c)) % MOD
def poly_hash_mod(s: str) -> int:
    h = 0
    for ch in s:
        h = (h * P + ord(ch)) % MOD
    return h

# 2) Вариант: uint64 overflow: h = h*P + ord(c) (переполнение 64-бит)
def poly_hash_u64(s: str) -> int:
    h = 0
    mask = (1 << 64) - 1
    for ch in s:
        h = (h * P + ord(ch)) & mask
    return h

# ВЫБЕРИ, какая у тебя функция:
HASH_FUNC = poly_hash_mod   # <-- поменяй на poly_hash_u64 если у тебя uint64 переполнение

# Алфавит слов (без пробелов)
ALPHABET = string.ascii_letters + string.digits  # a-zA-Z0-9

OUT_FILE = Path(f"poly_collisions_{NEEDED}.txt")
# -------------------------------------------

def bucket(s: str) -> int:
    return HASH_FUNC(s) % TABLE_LEN

def gen_word_base(k: int) -> str:
    # делаем гарантированно уникальную "базу"
    # например: w000, w001, ...
    return f"w{k:03d}"

def find_word_for_bucket(unique_set: set, target_bucket: int) -> str:
    """
    Подбирает слово, которое попадает в target_bucket.
    Делает это не "рандомом", а детерминированным перебором суффикса.
    """
    # берём уникальную базу и пытаемся дописать к ней суффикс так,
    # чтобы попали в нужный бакет
    # перебор суффиксов длины 1..4 (обычно хватает с запасом)
    base_id = len(unique_set)
    base = gen_word_base(base_id)

    for suf_len in range(1, 5):
        # полный перебор по небольшому алфавиту
        # чтобы не взорваться, ограничим алфавит для суффикса
        suf_alpha = string.ascii_lowercase  # 26 вариантов
        # перебираем все суффиксы данной длины
        # рекурсивно/итеративно: просто вложенные циклы до 4
        if suf_len == 1:
            for a in suf_alpha:
                w = base + a
                if w not in unique_set and bucket(w) == target_bucket:
                    return w
        elif suf_len == 2:
            for a in suf_alpha:
                for b in suf_alpha:
                    w = base + a + b
                    if w not in unique_set and bucket(w) == target_bucket:
                        return w
        elif suf_len == 3:
            for a in suf_alpha:
                for b in suf_alpha:
                    for c in suf_alpha:
                        w = base + a + b + c
                        if w not in unique_set and bucket(w) == target_bucket:
                            return w
        else:  # 4
            for a in suf_alpha:
                for b in suf_alpha:
                    for c in suf_alpha:
                        for d in suf_alpha:
                            w = base + a + b + c + d
                            if w not in unique_set and bucket(w) == target_bucket:
                                return w

    raise RuntimeError("Не удалось подобрать слово под нужный бакет. Увеличь TABLE_LEN или суффикс.")

def main():
    words = []
    used = set()

    for _ in range(NEEDED):
        w = find_word_for_bucket(used, TARGET_BUCKET)
        used.add(w)
        words.append(w)

    # контроль: все слова действительно в одном бакете
    b = bucket(words[0])
    assert all(bucket(w) == b for w in words), "Не все слова попали в один индекс!"
    assert len(words) == len(set(words)) == NEEDED, "Повторяющиеся слова!"

    OUT_FILE.write_text("\n".join(words) + "\n", encoding="utf-8")
    print(f"OK: {OUT_FILE} создан. Все {NEEDED} слов попадают в index={b} при TABLE_LEN={TABLE_LEN}.")

if __name__ == "__main__":
    main()