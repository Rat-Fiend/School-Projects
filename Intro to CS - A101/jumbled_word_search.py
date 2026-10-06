#########################################
# Quinton Odenthal
# Assignment 3
# 11/15/20
#
# Description: This program finds words from a jumble of letters.
# Inputs: A jumble of letters.
# Outputs: A list of words that contain the jumble of letters.
#########################################

f = open(r'C:\Users\quint\OneDrive\Desktop\School Code Testing\CSCE A101\words.txt', 'r')
contents = f.read()
f.close()

def txt_to_list(txt_file):
    word_list = txt_file.split()
    return word_list

def build_dict(word_list):
    """
    Description: This function creates a dictionary containing keys of sorted words with values of un-sorted words that contain the same letters.
    Inputs: List of words.
    Returned value: A dictionary.
    Preconditions: Input must be a list.
    """
    sorted_dict = {}
    for word in word_list:
        sorted_word = ''.join(sorted(word))
        if sorted_word in sorted_dict:
            sorted_dict[sorted_word].append(word)
        else:
            sorted_dict[sorted_word] = [word]
    return sorted_dict

def unscramble(jumble, sorted_dict):
    sorted_jumble = ''.join(sorted(jumble))
    if sorted_jumble in sorted_dict:
        print('{} unscrambles to: {}'.format(jumble, sorted_dict[sorted_jumble]))
    else:
        print('{} unscrambles to: No word found'.format(jumble))

words = txt_to_list(contents)
scramble_dict = build_dict(words)

user_jumble = str(input('Please enter a jumble to solve:'))

unscramble(user_jumble, scramble_dict)
unscramble('asewes', scramble_dict)
unscramble('enost', scramble_dict)
unscramble('aaabcs', scramble_dict)