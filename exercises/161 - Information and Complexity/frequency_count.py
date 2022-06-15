def frequency_count(input_string):
    count_dict = {}
    for c in input_string:
        if (not count_dict.get(c)):
            count_dict[c] = 1
        else:
            count_dict[c] = count_dict[c] + 1
    return count_dict