# Alarcon Ace Belen
# 201804736
# Language Used: Python 3

import sys

# See comment on compression ratio computation
import decimal
decimal.getcontext().rounding = decimal.ROUND_HALF_UP

def RLS_decode(code):
    ''' Decodes a compressed message `code` using run-length decoding

    Parameters
    ----------
    code : str
        Compressed message consisting of UTF-8 characters

    Returns
    -------
    out : str
        Decoded message
    '''
    
    out = ''

    # We set count as a string since it is 
    # easier to append a "digit" to a string 
    # than adding a digit to an int.
    count = ''

    # Iterate through the input data.
    for _char in code:
        
        # Whenever ASCII character 0-9 is encountered,
        # append the digit to the current count.
        if ord(_char) >= 48 and ord(_char) <= 57:
            count += _char
        
        # Non-numerical character '_char' is encountered.
        else:
            
            # Append the character repeated 
            # 'count' times to the output.
            if (count != ''):
                out += _char * int(count)
            else:
                out += _char
            # Reset count
            count = ''

    return out

# handles I/O simultaneously
# Accepts an input file 'input.txt'
# and write to an output file 'output.txt'.
# Assumes that an input file 'input.txt' exists
def handleIO(in_filename = "input.txt", out_filename = "output.txt"):

    if len(sys.argv) == 2:
        in_filename = sys.argv[1]
    if len(sys.argv) == 3:
        in_filename = sys.argv[1]
        out_filename = sys.argv[2]
    
    with open(in_filename, mode='r', encoding='utf8') as in_file,\
        open(out_filename, mode='w', encoding='utf8') as out_file:
        
        # number of test cases/codes
        T = int(in_file.readline())

        # list of compressed messages
        code_list = in_file.read().splitlines()

        # Iterate through the list of codes.
        for i in range(T):
            in_data = code_list[i]

            # decoded message
            out_data = RLS_decode(in_data)

            # compression ratio computation
            c_ratio = (len(out_data)/len(in_data))
            # Note that I did not use the built-in
            # round method due to its banker's
            # rounding behaviour in Python 3.
            c_ratio = str(decimal.Decimal(c_ratio).to_integral_value())
            
            out_file.write(c_ratio + ' ' + out_data + '\n')

if __name__ == "__main__":
    handleIO()