def get_ways(n):
    if n <= 0:
        return [[]]
    ways = []
    for i in range(1, 4):
        if n >= i:
            result = get_ways(n - i)
            # Prepending i to all the solutions in result:
            for j in range(len(result)):
                result[j] = [i] + result[j]
            ways += result
    return ways

print(get_ways(3))

import time

start_time = time.process_time()
get_ways(22) # no printing done
end_time = time.process_time()
print("get_ways(22): %.2f seconds" % (end_time - start_time))
