from random import randint
n = 0
for y in range(10):

    arq = open("funcionarios {}.txt".format(n),'w')
    n+=1
    for x in range(1000):
        arq.write(str(randint(100000, 999999))+'\n')