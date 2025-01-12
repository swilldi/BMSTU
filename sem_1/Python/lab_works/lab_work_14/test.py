# import os.path
# from struct import pack, unpack, calcsize
#
# from data_base_function import DATA_BITE
#
# p = "ii"
# step = calcsize(p)
#
# with open("dop.bin", "wb") as f:
#     d = pack(p, 10, 12)
#     f.write(d)
#     d = pack(p, 20, 30)
#     f.write(d)
#     d = pack(p, 39, 104)
#     f.write(d)
#     d = pack(p, 281, 94)
#     f.write(d)
#
# ind = 1
# elements_count = os.path.getsize("dop.bin") // step
# with open("dop.bin", "rb+") as f:
#     # выделяем место для новых данных
#     f.seek(ind * step, 0)
#     for i in range(1, elements_count - ind):
#         f.seek(step, 1)
#         data = f.read(step)
#         f.seek(-step * 2, 1)
#         f.write(data)
#     f.truncate()
#
# with open("dop.bin", "rb") as f:
#     while True:
#         try:
#             data = unpack(p, f.read(step))
#         except:
#             break
#         print(*data)
# import os
# print(os.path.getsize("/Users/dmitry/Documents/BMSTU/Programming/Python/lab_works/lab_work_14/new.bin"))
# a = "\udcd1".replace("\udcd1", "@")
# print(a)

# from struct import pack
# pattern="50sii"
# with open("database_files/films.bin", "wb+") as f_bin, open("database_files/films.txt") as f_txt:
#     while line:=f_txt.readline():
#         data = line.split(";")
#         f_bin.write(pack(pattern, data[0].encode("utf-8"), int(data[1]), int(data[2])))

import struct
print(struct.calcsize("i"))
