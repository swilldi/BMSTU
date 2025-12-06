n, m = map(int, input().split())
m_1 = [[0] * m for _ in range(n)]
while (line := input()):
    i, j, v = map(int, line.split())
    m_1[i - 1][j - 1] = v

p, q = map(int, input().split())
m_2 = [[0] * q for _ in range(p)]
while (line := input()):
    i, j, v = map(int, line.split())
    m_2[i - 1][j - 1] = v
    
m_3 = [[0] * q for _ in range(n)]
for i in range(n):
    for j in range(q):
        for k in range(m):
            m_3[i][j] +=  m_1[i][k] * m_2[k][j]

for i in range(n):
    for j in range(q):
        v = m_3[i][j]
        if (v != 0):
            print(f"{i + 1} {j + 1} {v}")