import math

epsilon = 1e-9

# Binary search (iterative version)
def binsearch(c):
    lower = 0.0
    upper = c
    while True:
        # Avoid any possible overflow when computing middle:
        middle  = lower + (upper - lower) / 2
        # n * lg(n):
        val = middle * math.log(middle, 2)
        if abs(c - val) <= epsilon:
            # Rounding down to integer 
            return int(middle)
        if val > c:
            upper = middle
        else:
            lower = middle

# Binary search (recursive version)
def binsearch_rec_helper(c, lower, upper):
    # Avoid any possible overflow when computing middle:
    middle = lower + (upper - lower)/ 2  #need to make smaller so no overflow 
    # n * lg(n):
    val = middle * math.log(middle, 2)
    if abs(c - val) <= epsilon:
        # Rouding down to integer: bc we cant go above the limit
        return int(middle)
    if val > c:
        return binsearch_rec_helper(c, lower, middle)
    else:
        return binsearch_rec_helper(c, middle, upper)

def binsearch_rec(c):
    return binsearch_rec_helper(c, 0.0, c)

print(binsearch(3600000000))
print(binsearch_rec(3600000000))
