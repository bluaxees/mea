import math

def estimated_mutual_information(xy_samples):
    x_frequency_count = {}
    y_frequency_count = {}
    xy_frequency_count = {}

    for pair in xy_samples:
        if (not y_frequency_count.get(pair[1])):
            y_frequency_count[pair[1]] = 1
        elif (y_frequency_count.get(pair[1])):
            y_frequency_count[pair[1]] = y_frequency_count[pair[1]] + 1
        if (not xy_frequency_count.get(pair)):
            xy_frequency_count[pair] = 1
        elif (xy_frequency_count.get(pair)):
            xy_frequency_count[pair] = xy_frequency_count[pair] + 1
        if (not x_frequency_count.get(pair[0])):
            x_frequency_count[pair[0]] = 1
        elif (x_frequency_count.get(pair[0])):
            x_frequency_count[pair[0]] = x_frequency_count[pair[0]] + 1

    ans = 0
    for tup in xy_frequency_count:
        prob_x_given_y = xy_frequency_count[tup]/y_frequency_count[tup[1]]
        prob_y = y_frequency_count[tup[1]]/len(xy_samples)
        prob_x = x_frequency_count[tup[0]]/len(xy_samples)
        log_num = prob_x_given_y/prob_x
        ans += prob_y * prob_x_given_y * math.log(log_num, 2)
    return ans
