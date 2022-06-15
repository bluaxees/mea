import time

def algorithm_time(func_name, n):
    start = time.perf_counter_ns()
    for i in range(n):
        func_name(*[i+1])
    return time.perf_counter_ns()-start

def algorithm_time(func_name, n, r):
    start = time.perf_counter_ns()
    for i in range(r):
        func_name(*[n])
    return time.perf_counter_ns()-start

def algebraic_sum(n):
    return int(n*(n+1)/2)

def iterative_sum(n):
    sum = 0
    for i in range(n):
        sum += i + 1
    return sum

def recursive_sum(array,l,r):
    if l == r:
        return array[l]
    else:
        if l == r-1:
            return array[l] + array[r]
        else:
            m  = int((l+r)/2)
            return recursive_sum(array,l,m) + recursive_sum(array,m+1,r)

def recursive_helper(n):
    array = [(i+1) for i in range(n)]
    return recursive_sum(array, 0, n-1)

if __name__=="__main__":

    n = 1440
    # print("N = ", n)
    # print("Algebraic performance: ", algorithm_time(algebraic_sum,n))
    # print("Iterative performance: ", algorithm_time(iterative_sum,n))
    # print("Recursive performance: ", algorithm_time(recursive_helper,n))

    n = 1000000
    r = 400
    print("N = ", n)
    print("R = ", r)
    print("Algebraic performance: ", algorithm_time(algebraic_sum,n,r))
    print("Iterative performance: ", algorithm_time(iterative_sum,n,r))
    print("Recursive performance: ", algorithm_time(recursive_helper,n,r))
