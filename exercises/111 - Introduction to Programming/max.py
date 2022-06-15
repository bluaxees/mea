def max(num_list):
    if len(num_list) == 1:
        return num_list
    elif num_list[len(num_list)-1] >= num_list[len(num_list)-2]:
        del num_list[len(num_list)-2]
    else:
        del num_list[len(num_list)-1]
    return max(num_list)
    
def main():
    num_list = [19,14,2,10,3,17,7,3,11,8,15]
    print(max(num_list))
    
if __name__ == "__main__":
    main()
