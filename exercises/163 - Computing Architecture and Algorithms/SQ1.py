def find_minimum_k(distances, k_check, k_m):
    
    # end tile is reached
    if (len(distances) == 0):
        return k_m
    
    # next tile cannot be reached
    if (k_check < distances[0]):
        return k_m + 1
    
    # distance skipped is exactly k units
    if (k_check == distances[0]):
        return find_minimum_k(distances[1:], k_check-1, k_m)
    
    return find_minimum_k(distances[1:], k_check, k_m)

if __name__ == "__main__":
    tiles = [1, 7, 8, 12, 15, 20, 25]
    distances = [(tiles[i + 1] - tiles[i]) for i in range(len(tiles) - 1)]
    print(distances)
    
    k_m = max(distances)
    k = find_minimum_k(distances, k_m, k_m)
    print(k)


# 2 3 3 4 3 4 4

# 1 1 2 1 2 2 3

