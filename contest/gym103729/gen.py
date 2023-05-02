n = int(1e5)
import string
import random

s=[]
for _ in range(n//2):
	s.append( random.choice(string.ascii_letters) )
s += list(reversed(s))

l,r  = 8901, int(9e4)

while l < r:
	s[l], s[r] = s[r], s[l]
	l += 1
	r -= 1

import clipboard
m=''
for i in s: m += i
print(m)
