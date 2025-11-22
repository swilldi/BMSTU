import random
import string

words_count = [
    100,
    500,
    1_000,
    5_000,
    10_000,
    50_000,
    100_000
]

for count in words_count:
    filename = f"test_{count}.txt"
    num_lines = count
    # Гарантируем, что хотя бы несколько слов на 'b' будут
    num_b_words = 50

    def random_word(min_len=3, max_len=8):
        return ''.join(random.choices(string.ascii_lowercase, k=random.randint(min_len, max_len)))

    with open(filename, "w") as f:
        for i in range(num_lines):
            num_words = random.randint(3, 6)
            words = []

            for _ in range(num_words):
                # Иногда вставляем слово на 'b'
                if num_b_words > 0 and random.random() < 0.05:  # 5% шанс
                    word = 'b' + random_word()
                    num_b_words -= 1
                else:
                    word = random_word()
                words.append(word)
            line = ' '.join(words)
            f.write(line + '\n')