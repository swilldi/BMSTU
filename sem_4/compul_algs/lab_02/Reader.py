
def read_data_from_file():
    f = open("data.txt")

    data = []
    z = 0
    cur_x = []
    is_x_line = False
    
    while line := f.readline():

        if line == '\n':
            continue

        nums = list(map(int, line.split()))

        if len(nums) == 1:
            z = nums[0]
            is_x_line = True
        elif is_x_line:
            is_x_line = False
            cur_x = nums
        else:
            y = nums[0]
            for i in range(len(cur_x)):
                data.append((cur_x[i], y, z, nums[i + 1]))

    f.close()

    return data