import math

def count_bad_channels(blocklength, erasure_prob):

    channels = [erasure_prob]
    for i in range(int(math.log2(blocklength))):
        temp = channels.copy()
        for i, p in enumerate(channels):
            i *= 2
            temp[i] = 2*p - p**2
            temp.insert(i+1, p**2)
        channels = temp.copy()
    
    ans = 0
    for p in channels:
        if p > erasure_prob:
            ans += 1 
    
    return ans