import random, math

def exact_entropy(dist):
    return sum([-p*math.log2(p) for p in dist.values() if p > 0])

def estimated_entropy(samples, dist):
    return sum([-samples.count(x)/len(samples) * math.log2(dist[x]) for x in set(samples) if dist[x] > 0])

def jointly_typical(x, y, joint_dist, epsilon):
    if len(x) != len(y):
        raise ValueError('x and y must have equal lengths.')
    elif epsilon <= 0:
        raise ValueError('epsilon must be strictly positive.')
    else:
        row_length = [len(joint_dist[i]) for i in range(len(joint_dist))]
        if any([row_length[i] != row_length[0] for i in range(1, len(row_length))]):
            raise ValueError('All rows of joint_dist must have equal lengths.')
    
    xy = [(x[i], y[i]) for i in range(len(x))]
    x_alphabet = range(len(joint_dist))
    y_alphabet = range(len(joint_dist[0]))

    x_prob = {x: sum([joint_dist[x][y] for y in y_alphabet]) for x in x_alphabet}
    y_prob = {y: sum([joint_dist[x][y] for x in x_alphabet]) for y in y_alphabet}
    xy_prob = {(x,y): joint_dist[x][y] for x in x_alphabet for y in y_alphabet}

    Hx = exact_entropy(x_prob)
    Hy = exact_entropy(y_prob)
    Hxy = exact_entropy(xy_prob)

    return max([abs(Hx - estimated_entropy(x, x_prob)), abs(Hy - estimated_entropy(y, y_prob)), abs(Hxy - estimated_entropy(xy, xy_prob))]) < epsilon

def typical_set_codec(channel, x_dist, frame_len, block_len, num_frames, epsilon):
    
    # k = frame_len
    # n = block_len
    # num_frames = number of transmissions over the channel

    # input alphabet X
    # {0, 1} for a BSC
    x_alphabet = [i for i in range(len(x_dist))]
    
    # output alphabet y
    # {0, 1} for a BSC
    y_alphabet = [i for i in range(len(channel[0]))]

    # create codebook of size ...
    codebook = []

    # 2**k by...
    for i in range(2**frame_len):
        encoder_input = []
        # n
        for j in range(block_len):
            # use x_dist to generate codebook
            encoder_input.append(random.choices(x_alphabet, x_dist)[0])
        codebook.append(encoder_input)

    channel_outputs = []
    for i in range(num_frames):

        # random.randrange(2**frame_len) = select i from source
        # source will be from 0 to (2**frame_len)-1
        # access codebook[i]
        channel_input = codebook[random.randrange(2**frame_len)]
        channel_output = []

        # transmit codebook[i] over channel
        for j in channel_input:

            # transform input x^n to y^n using channel probability
            channel_output.append(random.choices(y_alphabet, channel[int(j)])[0])
        
        # append to 
        channel_outputs.append(channel_output)

    # derivation of the joint distribution
    joint_dist = []
    for i, x in enumerate(channel):
        joint_x = []
        for y in x:
            joint_x.append(y*x_dist[i])
        joint_dist.append(joint_x)

    error = 0
    for co in channel_outputs:
        count = 0
        # for all entries in the codebook ...
        for code in codebook:
            # check if received y^n is e-typical with entry
            if (jointly_typical(code, co, joint_dist, epsilon)):
                count += 1
        # if the number of entries e-typical with received y^n ...
        # is not 1, report an error
        if (count != 1):
            error += 1
    return error/num_frames

def main():
    p = 0.001
    channel = [[1-p, 0, p], [0, 1-p, p]]
    x_dist = [0.5, 0.5]
    frame_len = 1
    block_len = 100
    epsilon = 0.02
    num_frames = 10000
    total_error = 0
    runs = 10
    print(typical_set_codec(channel, x_dist, frame_len,\
            block_len, num_frames, epsilon))

if __name__ == "__main__":
    main()