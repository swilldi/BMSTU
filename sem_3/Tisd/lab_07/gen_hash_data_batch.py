#!/usr/bin/env python3
import os
import random
from collections import defaultdict, Counter

def hash_string(s):
    """Вычисляет хэш строки как сумму кодов символов"""
    return sum(ord(c) for c in s)

def generate_string_with_sum(target_sum, existing):
    """
    Детерминированно строит строку с заданной суммой кодов (печатаемые ASCII 33-126),
    уникальную относительно existing.
    """
    min_char = 33
    max_char = 126
    # Будем пробовать разную длину: сначала короткие
    max_len = max(1, target_sum // min_char + 2)
    for length in range(1, max_len + 10):
        base_sum = min_char * (length - 1)
        remaining = target_sum - base_sum
        if remaining < min_char or remaining > max_char:
            continue
        s = "!" * (length - 1) + chr(remaining)
        if s not in existing and hash_string(s) == target_sum:
            return s
    return None


def generate_unique_strings(count, collision_percent):
    """
    Генерирует набор уникальных строк с заданным процентом коллизий.
    Гарантирует длину списка count.
    """
    strings = []
    by_hash = defaultdict(list)

    target_collision = max(0, (count * collision_percent) // 100)
    target_non_collision = count - target_collision

    # 1) Набираем строки с уникальными хэшами.
    i = 0
    while len(strings) < target_non_collision:
        s = f"x{i:08d}"
        h = hash_string(s)
        if h not in by_hash:
            strings.append(s)
            by_hash[h].append(s)
        i += 1

    # 2) Добираем коллизии на уже существующие хэши.
    existing_hashes = list(by_hash.keys())
    attempts_left = target_collision * 20 + 1000
    while len(strings) < count and attempts_left > 0:
        attempts_left -= 1
        if not existing_hashes:
            break
        target_hash = random.choice(existing_hashes)
        s = generate_string_with_sum(target_hash, set(strings))
        if s:
            strings.append(s)
            by_hash[target_hash].append(s)

    # 3) Если недобрали, добиваем уникальными хэшами, чтобы длина была count.
    j = 0
    while len(strings) < count:
        s = f"z{j:08d}"
        h = hash_string(s)
        if s not in strings:
            strings.append(s)
            by_hash[h].append(s)
        j += 1

    random.shuffle(strings)
    return strings, by_hash

def summarize_collisions(strings):
    """Возвращает Counter по хэшам и фактический процент коллизий."""
    hashes = [hash_string(s) for s in strings]
    counts = Counter(hashes)
    total = len(strings)
    colliding = sum(c for c in counts.values() if c > 1)
    percent = (colliding * 100) // total if total else 0
    return counts, percent

def create_hash_data_files():
    """Создает файлы с данными для тестирования"""
    
    # Параметры
    counts = [10, 20, 50, 100, 200, 500, 1000, 5000, 10000]
    collision_percents = [0, 10, 30, 50, 70, 90]
    
    # Создаем папку
    output_dir = "hash_data_collision"
    os.makedirs(output_dir, exist_ok=True)
    
    total_files = len(counts) * len(collision_percents)
    current_file = 0
    
    for count in counts:
        for collision_percent in collision_percents:
            current_file += 1
            filename = f"{count}_{collision_percent}.txt"
            filepath = os.path.join(output_dir, filename)
            
            print(f"[{current_file}/{total_files}] Генерирую {filename}...", end=" ", flush=True)
            
            # Генерируем данные
            strings, by_hash = generate_unique_strings(count, collision_percent)
            _, fact_percent = summarize_collisions(strings)
            
            # Записываем в файл
            with open(filepath, 'w') as f:
                for s in strings:
                    f.write(s + '\n')
            
            print(f"OK ({len(strings)} строк, факт. коллизий ~{fact_percent}%)")
    
    print(f"\nВсе файлы созданы в папке '{output_dir}'")

if __name__ == "__main__":
    random.seed(42)  # Для воспроизводимости
    create_hash_data_files()
