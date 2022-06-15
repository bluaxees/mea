import sys

ALOG_TABLE = []
LOG_TABLE = [0]*256
EC_LEVELS = {'L':0, 'M':1, 'Q':2, 'H':3}
CW_LENGHTS = [[7, 10, 13, 17], [10, 16, 22, 28]]

def init_table(n=0x100, generator=0x11d):
    temp = 1
    for i in range(n-1):
        ALOG_TABLE.append(temp)
        LOG_TABLE[temp] = i
        temp <<= 1
        if (temp & n):
            temp ^= generator
    ALOG_TABLE.append(1)

def init_gen_poly(c):
    gen_poly = [0]
    for i in range(1,c):
        gen_poly.append(0)
        gen_temp = list(map(lambda g: (g+i)%255, gen_poly))
        for j in range(len(gen_temp)-1, -1, -1):
            gen_poly[j] = LOG_TABLE[ALOG_TABLE[gen_temp[j]]^\
                ALOG_TABLE[gen_poly[j-1]]]
        gen_poly[0] = gen_temp[0]
    gen_poly.append(0)
    return gen_poly

def get_rs_code(data, num_cw, d_size):
    gen_poly = init_gen_poly(num_cw)
    gen_poly.reverse()
    data_ = data.copy()
    data.extend([0 for i in range(num_cw)])
    for i in range(d_size):
        
        h_term = LOG_TABLE[data[i]]
        if (h_term != 0 or data[i] == 1):
            for j in range(1,len(gen_poly)):
                if(gen_poly[j] != 0):
                    data[i+j] ^= ALOG_TABLE[(gen_poly[j]+h_term)%255]
    return data[d_size:]

def handleIO(in_filename = "input.txt", out_filename = "output.txt"):

    init_table()

    if len(sys.argv) == 2:
        in_filename = sys.argv[1]
    if len(sys.argv) == 3:
        out_filename = sys.argv[2]
    
    with open(in_filename, mode='r') as in_file,\
        open(out_filename, mode='w') as out_file:
        T = int(in_file.readline())
        out_data = []
        for i in range(T):
            V, C, D = in_file.readline().split()
            in_data = list(map(int, in_file.readline().split()))
            num_cw = CW_LENGHTS[int(V)-1][EC_LEVELS[C.capitalize()]]
            out_data = get_rs_code(in_data, num_cw, int(D))
            out_file.write(' '.join(str(s) for s in out_data)+'\n')

if __name__ == "__main__":
    handleIO()