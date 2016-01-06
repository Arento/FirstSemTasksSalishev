def check(f,n):
    c = len(f)//3
    if f[c] == n:
        return 0
    elif f[c]>n:
        return 2 + check(f[:c],n)
    elif f[c]<n:
        return 1 + check(f[c+1:],n)
    
f = [x+1 for x in range(100)]
ans = 0
for i in range(100):
    ans = max(ans,check(f,i+1))
print(ans)
