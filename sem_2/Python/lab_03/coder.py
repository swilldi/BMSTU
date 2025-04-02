'''
Первые 3 пикселей занимает кол-во символов ы предложении
'''

class Coder:
    from PIL import ImageFile
    PIXEL_LEN = 3

    def __init__(self, pixels: list[ImageFile] = [], message: str = ""):
        self.pixels = pixels
        self.message = message

    def encode(self):
        # первые три пикселя сохраняют длину сообщения
        length = len(self.message)
        shift = 7
        for i in range(self.PIXEL_LEN):
            old_pixel = self.pixels[i]
            new_pixel = [0, 0, 0]
            for j in range(3):
                if i != 0 and i % 2 == 0 and j == 2:
                    new_pixel[j] = old_pixel[j]
                    break
                if length & 1 << shift:
                    new_pixel[j] = old_pixel[j] | 1 << shift
                else:
                    new_pixel[j] = old_pixel[j] & ~(1 << shift)
                shift -= 1
            self.pixels[i] = tuple(new_pixel)
            if shift < 0:
                shift = 7

        # кодирование сообщения
        start = self.PIXEL_LEN
        for symbol in self.message:
            code = ord(symbol)
            shift = 7
            for p_ind in range(start, start + self.PIXEL_LEN):
                new_pixel = [0, 0, 0]
                pixel = self.pixels[p_ind]
                for i in range(3):
                    if code & 1 << shift:
                        new_pixel[i] = pixel[i] | 1 << shift
                    else:
                        new_pixel[i] = pixel[i] & ~(1 << shift)

                    if shift == 0:
                        break
                    else:
                        shift -= 1
                self.pixels[p_ind] = tuple(new_pixel)
            start += self.PIXEL_LEN

    def decode(self):
        # получение длины сообщения из первых 3-х символов
        length = 0
        shift = 7
        for i in range(self.PIXEL_LEN):
            for j in range(3):
                if i != 0 and i % 2 == 0 and j == 2:
                    break
                length += self.pixels[i][j] & 1 << shift
                shift -= 1

        # декодирование сообщения
        start = self.PIXEL_LEN
        for _ in range(length):
            code = 0
            shift = 7
            for pixel in self.pixels[start:start + self.PIXEL_LEN]:
                for i in range(3):
                    code |= pixel[i] & 1 << shift
                    # if code & 1 << shift:
                    #     new_pixel[i] = pixel[i] | 1 << shift
                    # else:
                    #     new_pixel[i] = pixel[i] & ~(1 << shift)

                    if shift == 0:
                        break
                    else:
                        shift -= 1
            self.message += chr(code)
            start += self.PIXEL_LEN