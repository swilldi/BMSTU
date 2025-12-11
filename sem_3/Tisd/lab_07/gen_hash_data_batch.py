#!/usr/bin/env python3
import os
import random
import string
from collections import defaultdict

def hash_string(s):
    """Вычисляет хэш строки как сумму кодов символов"""
    return sum(ord(c) for c in s)

def generate_unique_strings(count, collision_percent):
    """
    Генерирует набор уникальных строк с заданным процентом коллизий.
    
    Args:
        count: количество элементов
        collision_percent: процент элементов, которые должны иметь коллизии (0-100)
    
    Returns:
        список уникальных строк
    """
    strings = []
    hash_map = defaultdict(list)
    
    # Определяем сколько строк должны быть в коллизиях
    collision_count = max(0, (count * collision_percent) // 100)
    
    # Количество строк, которые должны быть без коллизий
    non_collision_count = count - collision_count
    
    # Для 0% коллизий используем специальную стратегию
    if collision_percent == 0:
        # Создаем строки с разными хэшами
        for i in range(count):
            # Генерируем строку с контролируемым хэшем
            # Используем простой подход: кодируем номер в строку
            s = f"x{i:08d}"  # "x" + 8-значный номер
            strings.append(s)
            h = hash_string(s)
            hash_map[h].append(s)
    else:
        # Генерируем строки без коллизий
        for i in range(non_collision_count):
            s = f"a{i:08d}"  # "a" + 8-значный номер
            strings.append(s)
            h = hash_string(s)
            hash_map[h].append(s)
        
        # Генерируем строки с коллизиями
        # Выбираем случайные хэши из уже созданных строк
        if strings:
            for _ in range(collision_count):
                # Выбираем случайную существующую строку и создаем коллизию
                target_string = random.choice(strings)
                target_hash = hash_string(target_string)
                
                # Генерируем новую строку с тем же хэшем
                attempts = 0
                while attempts < 1000:
                    s = generate_string_with_hash(target_hash, set(strings))
                    if s is not None:
                        strings.append(s)
                        break
                    attempts += 1
    
    # Перемешиваем
    random.shuffle(strings)
    
    return strings

def generate_string_with_hash(target_hash, existing_strings):
    """
    Генерирует строку с заданной суммой кодов символов (хэшем).
    Строка должна быть уникальна.
    """
    max_attempts = 5000
    
    for _ in range(max_attempts):
        # Стратегия: строим строку с контролем суммы
        length = random.randint(3, 20)
        chars = []
        current_sum = 0
        
        for i in range(length):
            remaining = target_hash - current_sum
            remaining_chars = length - i - 1
            
            # Вычисляем допустимый диапазон для символа
            if remaining_chars == 0:
                # Последний символ - должен дать остаток
                if 32 <= remaining <= 126:
                    chars.append(chr(remaining))
                    current_sum += remaining
                else:
                    break
            else:
                # Не последний символ
                # Среднее значение, которое нам нужно на оставшихся позициях
                avg_needed = remaining // (remaining_chars + 1)
                
                # Выбираем символ в допустимом диапазоне ASCII (32-126)
                min_val = max(32, avg_needed - 40)
                max_val = min(126, avg_needed + 40)
                
                if min_val > max_val:
                    break
                
                c_val = random.randint(min_val, max_val)
                chars.append(chr(c_val))
                current_sum += c_val
        
        s = ''.join(chars)
        
        # Проверяем условия
        if s and len(s) > 0 and s not in existing_strings:
            if hash_string(s) == target_hash:
                return s
    
    return None

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
            strings = generate_unique_strings(count, collision_percent)
            
            # Записываем в файл
            with open(filepath, 'w') as f:
                for s in strings:
                    f.write(s + '\n')
            
            print(f"OK ({len(strings)} строк)")
    
    print(f"\nВсе файлы созданы в папке '{output_dir}'")

if __name__ == "__main__":
    random.seed(42)  # Для воспроизводимости
    create_hash_data_files()
