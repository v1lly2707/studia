#zad1
def linear_generator(A,C,M,seed,prev=0):
    if prev == 0:
        prev = seed%M

    prev = (A*prev + C) % M

    return prev


a = 69069
c = 1
M = 2**31
n = 100000
seed = 1

    
def shift_generator(p, q, begin, targ):
    for i in range(p,31):
        begin.append((begin[i-p]^begin[i-q])) #wzor

    num = 0
    for i in range(len(begin)):
        if begin[i] == 1:
            num += 2**i

    targ.append(num)

    return begin[-7:]

previous = linear_generator(a, c, M, seed)
decom =[0]*10

for i in range(n):
    previous = linear_generator(a, c, M, seed, previous)
    
    for j in range(10):
        if previous < (j+1) * 0.1 * M:
            decom[j] += 1
            break


print("Linear generator:")
print(decom)

#zad2
targ = []
begin1 = [1,1,0,1,1,0,1]

decom2 = [0]*10

next = shift_generator(7,3,begin1,targ)

for i in range(100000):
    next = shift_generator(7,3,next,targ)


for i in range(len(targ)):
    for j in range(10):
        if targ[i] < (j+1) * 0.1 * M:
            decom2[j] += 1
            break
print("Shift generator:")
print(decom2)
