# Module: IFFT
# Desc: Inverse split-radix fast fourier transform
# Author: Alarcon Ace Belen
# DATE: Sunday, May 30th 2021
# Language Used: Python3

from cmath import exp
from math import pi

import decimal
decimal.getcontext().rounding = decimal.ROUND_HALF_UP

import sys

# Helper function that gets a complex number's 
# real part rounded to the nearest integer
def get_real_rounded(complex_num, norm=1):
    return str(decimal.Decimal(\
        complex_num.real/norm).to_integral_value())

# Helper function that computes the 
# twiddle factor given N and k.
def get_twiddle_factor(N,k):
    return exp((2j*pi*k)/N)

def sr_ifft(signal, N):

    """ Split-radix IFFT

    Parameters
    ----------
    signal : list
        Array of complex numbers corresponding 
        to data points in the signal
    N : int
        Size of the signal

    Returns
    -------
    signal : list
        Array of complex numbers corresponding 
        to data points of the computed DFT

    """

    # Base Cases
    # These root from the inverse DFT formula 
    # where Euler's identity is expanded
    if N == 1:
        return signal
    if N == 2:
        return [signal[0]+signal[1], signal[0]-signal[1]]
    
    # Split the signal into three: even, odd_1 and odd_3.
    # Use recursion to get the DFT of each sub-signal.
    N_over2 = N >> 1
    N_over4 = N >> 2
    signal = sr_ifft(signal[::2], N_over2) + \
            sr_ifft(signal[1::4], N_over4) + \
            sr_ifft(signal[3::4], N_over4)

    for k in range(N_over4):

        # Necessary terms to solve each quarter
        xn_even = signal[k]
        xn_even_N4 = signal[k+N_over4]
        xn_odd_1 = signal[k+(N_over2)]
        xn_odd_3 = signal[k+(3*N_over4)]
        omega_1 = get_twiddle_factor(N,k)
        omega_3 = get_twiddle_factor(N,3*k)
        
        # Precompute sum and difference of odd terms
        sum_odd = omega_1*xn_odd_1 + omega_3*xn_odd_3
        diff_odd = omega_1*xn_odd_1 - omega_3*xn_odd_3

        # Computation and merging of quarters
        signal[k] = xn_even + sum_odd
        signal[k+N_over2] = xn_even - sum_odd
        signal[k+(3*N_over4)] = xn_even_N4 - 1j*diff_odd
        signal[k+N_over4] = xn_even_N4 + 1j*diff_odd

    return signal

def handleIO():

    """ Handles IO simultaneously

    Running this script will read data from a file named 
    "input.txt" and write to a file "output.txt" by default.
    
    You may also run `python ME1-164-IFFT.py < in > < out >` 
    where < in > and < out > are the names of the input and 
    output files, respectively. The parameter < out > may be 
    undefined, which will output a file with the default name.

    """

    in_filename = "input.txt"
    out_filename = "output.txt"
    if len(sys.argv) == 2:
        in_filename = sys.argv[1]
    if len(sys.argv) == 3:
        in_filename = sys.argv[1]
        out_filename = sys.argv[2]
    
    with open(in_filename, mode='r') as in_file,\
        open(out_filename, mode='w') as out_file:
        
        num_testcases = int(in_file.readline())
        out_file.write(str(num_testcases)+'\n')
        
        # Iterate through the test cases
        for i in range(num_testcases):
            in_line = list(in_file.readline().split())
            
            output_len = int(in_line[0])
            input_len = int(in_line[1])
            in_data = list(map(complex, in_line[2:]))
            
            # Get output signal
            out_data = sr_ifft(in_data, input_len)

            # Format the output such that it is
            # compatible with the FFT module.
            out_data = list(map(lambda c:\
                get_real_rounded(c, input_len), out_data))[:output_len]
            out_string = str(output_len)+' '+' '.join(out_data)+'\n'

            out_file.write(out_string)

if __name__ == "__main__":
    handleIO()