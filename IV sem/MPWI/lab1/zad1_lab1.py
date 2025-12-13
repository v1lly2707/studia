def gen_permutation(n,m):
        def permute(cities,m,prefix=[]):
                if m == 0:
                        result.append(prefix)
                        return
                
                for i in range (len(cities)):
                        permute(cities[:i] + cities[i+1:],m-1, prefix + [cities[i]])

        cities = list(range(1,n+1))
        result = []

        permute(cities,m)

        for i, perm in enumerate(sorted(result), start = 1):
                print(f"{i}. {perm}")


n = 6
fact = 1

for i in range(1, n+1):
    fact = fact * i

m = 3
fact1 = 1

for i in range(1,n-m+1):
    fact1 = fact1 * i


a = fact / fact1

print(a)

gen_permutation(n,m)


def gen2(n,m):
    def subset(cities,m,prefix=[], start = 0):
        if m == 0:
            result.append(prefix)
            return
        for i in range(start,len(cities)):
            subset(cities, m-1,prefix+[cities[i]],i)

    cities = list(range(1,n+1))
    result = []
    subset(cities,m)
    for i, sub in enumerate(sorted(result), start=1):
        print(f"{i}. {sub}")
        #print(i)
       




a = 3
b = 6

fact2 = 1

for i in range(1, a+b):
    fact2 = fact2 * i


fact3 = 1

for i in range(1,a):
    fact3 = fact3 * i


fact4 = 1

for i in range(1,b+1):
      fact4 = fact4 * i

wyn = fact2 / (fact3*fact4)


print("\n")
print(wyn)

gen2(a,b)