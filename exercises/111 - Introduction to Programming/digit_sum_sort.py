def sort_by_digit_sum(numbers):
    def digit_sum(n):
        sum = 0
        # Repeat while n is non-zero
        while n:
            digit = n % 10
            sum += digit
            n /= 10
        return sum
    #return sorted(numbers, key=digit_sum)
    return sorted(numbers)

list_of_numbers = [100, 423, 199, 200, 128]
print(list_of_numbers)
sorted_list = sort_by_digit_sum(list_of_numbers)
print(sorted_list)
