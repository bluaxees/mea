from cmath import exp
from math import pi, sqrt

import sys
from os import walk

Wm_ = {}

def get_real_as_int(complex_num):
    return int(complex_num.real)

def omega_dict_init(N):
    global Wm_
    for k in range(N):
        Wm_[k] = exp(-2j*pi*k/N)

def W(N,k):
    return exp((-2j*pi*k)/N)

def sr_fft_recursive(signal, N):
    out = signal.copy()
    if N == 1:
        return signal
    if N == 2:
        return [signal[0]+signal[1], signal[0]-signal[1]]

    N_over2 = N >> 1
    N_over4 = N >> 2
    signal = sr_fft_recursive(signal[::2], N_over2) + sr_fft_recursive(signal[1::4], N_over4) + sr_fft_recursive(signal[3::4], N_over4)
    
    for k in range(N_over4):

        Xk_even = signal[k]
        Xk_even_N4 = signal[k+N_over4]
        sum_odd = W(N,k)*signal[k+(N_over2)] + W(N,3*k)*signal[k+(3*N_over4)]
        dif_odd = W(N,k)*signal[k+(N_over2)] - W(N,3*k)*signal[k+(3*N_over4)]

        out[k] = Xk_even + sum_odd
        out[k+N_over2] = Xk_even - sum_odd
        out[k+N_over4] = Xk_even_N4 - 1j*dif_odd
        out[k+(3*N_over4)] = Xk_even_N4 + 1j*dif_odd
    
    return out

def helper(c):
    a = "%0.6f"%(round(c.real, 6))
    if c.real >= 0:
        a = '+'+a
    b = "%0.6f"%(round(c.imag, 6))
    if c.imag >= 0:
        b = '+'+b
    return a + b + 'j'

def normalize(data, n):
    if not ((n & (n-1) == 0) and n != 0):
        n = 2**n.bit_length()

    for i in range(n-len(data)):
        data.append(0)

    return data, n

def handleIO(in_filename = "input.txt", out_filename = "output.txt"):

    if len(sys.argv) == 2:
        in_filename = sys.argv[1]
    if len(sys.argv) == 3:
        in_filename = sys.argv[1]
        out_filename = sys.argv[2]

    path = "."
    _, _, a = next(walk(path))
    #in_filename = a[int(len(a)/2)]
    #out_filename = path + "out" + in_filename[2:]
    #in_filename = path + in_filename
    
    with open(in_filename, mode='r') as in_file,\
        open(out_filename, mode='w') as out_file:
        T = int(in_file.readline())
        out_file.write(str(T) + '\n')
        for i in range(T):
            _in = list(in_file.readline().split())
            
            output_len = int(_in[0])
            #print(_in[2:])
            b = output_len
            in_data = list(map(int, _in[1:]))
            in_data, output_len = normalize(in_data,output_len)
            
            omega_dict_init(output_len)
            out_data = sr_fft_recursive(in_data, output_len)
            x = str(b) + ' ' + str(output_len) + ' ' + ' '.join(helper(s) for s in out_data)+'\n'
            out_file.write(x)

if __name__ == "__main__":
    handleIO()
