def rotate_counterclockwise(M, n):
    for i in range(n // 2):
        for j in range(i, n - 1 - i):
            M[i][j], M[j][n - 1 - i], M[n - 1 - i][n - j - 1], M[n - j - 1][i] = M[j][n - 1 - i], M[n - 1 - i][
                n - j - 1], M[n - j - 1][i], M[i][j]
    return M

with open("enc.txt", "r") as e, open("key.txt", "r") as k:
    l = k.read().split('\n')[:-1]
    M = []
    for i in l:
        a = [int(j) for j in bin(int(i))[2:]]
        a = (len(l) - len(a))*[0]+a
        M.append(a)
    n = len(M)
    decode = ''
    string = e.read()
    s = [[0] * n for i in range(n)]
    for i in range(n):
        for j in range(n):
            s[i][j] = string[0]
            string = string[1:]
    M = rotate_counterclockwise(M, n)
    for k in range(4):
        for i in range(n-1, -1, -1):
            for j in range(n-1, -1, -1):
                if M[i][j] == 1:
                    decode += s[i][j]
        M = rotate_counterclockwise(M, n)
    print(decode[::-1])


