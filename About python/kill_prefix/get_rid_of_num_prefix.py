f = open('C:\\Users\\Dell\\Desktop\\code.txt', 'r+')
g = open('C:\\Users\\Dell\\Desktop\\final_code.txt', 'r+')
flag = 0
for line in f.readlines():
    flag = 0
    z = list(line)
    for i in range(len(line)):
        if line[i] <= '9' and line[i] >= '0':
            flag = 1
            z[i] = ' '
        elif line[i] == ' ' and flag == 0:
            z[i] = ' '
        else:
            g.write("".join(z))
            break
f.close()
g.close()