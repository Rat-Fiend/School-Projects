import re

# phrase = " Hello Myra, you can email me at automata907@alaska.org or visit the website at alaska.org/automata and learn about the theory of computing! Or call me at 907.786.1956. Another way to learn about automata is to visit 192.229.210.176/automata_theory/index.htm or to go to https://en.wikipedia.org/wiki/Automata_theory for more information. Mr.Goo posted in section 999.10.34.997 about the equivalence between finite state automata and regular expressions. He regularly updates www.automata.com with the latest developments. "
phrase = " www.automata.com https://en.wikipedia.org/wiki/Automata_theory 192.229.210.176/automata_theory/index.htm "

phrase = phrase.lower()

global urls
urls = [str]

def addUrl(newUrl):     #Adds a url string to a list when one is found
    global urls
    urls.append(newUrl)

# def incChar():          #Increments the index along the phrase and sets the currChar to the char at that index
#     global i
#     if i >= len(phrase) - 1:
#         True
#     else:
#         i += 1
#         global currChar
#         currChar = phrase[i]

def findNum():
    newVal = re.search('\d{1,3}', phrase[i:i+3])       #Finds the first 1-3 length number in the 3 chacters infront of, and including index i
    newOutput = (newVal.group(0) if newVal else '-1')
    global currNum
    currNum = int(newOutput)
    return currNum

def find_ip():
    newVal = re.search(r'\b((?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?\.){3}'
                       r'(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))[^\b]*)', phrase)
    return newVal





# def skipNum():      #Skips over length of a digit to reach next character
#     if currNum < 10:    #currNum is one digit long so skip one digit
#         incChar()
#     elif currNum < 100: #currNum is two digits long so skip two digits
#         incChar()
#         incChar()
#     else:               #currNum is three digits long so skip three digits
#         incChar()
#         incChar()
#         incChar()

# def aCase():
#     incChar()
#     if i >= len(phrase) - 1:
#         True
#     elif currChar == ' ':
#         bCase()
#     elif currChar == '@':
#         zCase()
#     elif currChar == '.':
#         urlCase()
#         bCase()
#     else:
#         aCase()

# def bCase():
#     incChar()
#     if i >= len(phrase) - 1:
#         True
#     elif currChar == ' ':
#         bCase()
#     elif currChar == '@':
#         zCase()
#     elif currChar == '.':
#         aCase()
#     elif currChar == 'h':       #Potential start of http url
#         httpCase()
#         bCase()
#     elif 0 <= findNum() <= 255:    #Potential start of IP address url
#         ipCase()
#         bCase()
#     else:
#         aCase()

# def httpCase():
#     incChar()
#     if currChar == ' ':
#         bCase()
#     elif currChar == '@':
#         zCase()
#     elif currChar == 't':
#         incChar()
#         if currChar == 't':
#             incChar()
#             if currChar == 'p':         #Start of an http url
#                 start = i-3             #Index of h in http url
#                 while currChar != ' ':
#                     incChar()
#                 end = i                 #Index of last character of http url (+1 for add function boundry)
#                 addUrl(phrase[start:end])
#     else:
#         aCase()

# def ipCase():
#     skipNum()                           #Index is pointing at char following currNum
#     if currChar == ' ':
#         bCase()
#     elif currChar == '@':
#         zCase()
#     elif currChar == '.':
#         incChar()
#         if 255 >= findNum() >= 0:
#             skipNum()                   #Index is pointing at char following currNum
#             if currChar == '.':         #Start of an http url
#                 incChar()
#                 if 255 >= findNum() >= 0:
#                     skipNum()               #Index is pointing at char following currNum
#                     if currChar == '.':
#                         incChar()
#                         if 255 >= findNum() >= 0:   #If true, we are currently inside of a ip url until the next whitespace
#                             skipNum()               #Index is pointing at char following currNum
#
#                             j = i
#                             while phrase[j] != ' ': #after loop, j will be pointing at the first whitespace before our ip address
#                                 j -= 1
#                             start = j + 1
#
#                             while currChar != ' ':  #After loop, i will be pointing at first whitespace after ip address url
#                                 incChar()
#                             end = i
#                             addUrl(phrase[start:end])   #Adds newly found url to url list
#     else:
#         aCase()

# def urlCase():
#     incChar()
#     if currChar == ' ':
#         bCase()
#     elif currChar == '@':
#         zCase()
#     elif currChar == 'c':
#         incChar()
#         if currChar == 'o':
#             incChar()
#             if currChar == 'm':         #End of .com url / Start of file extention
#                 while currChar != ' ':  #End of file extention
#                     incChar()
#                 end = i
#                 j = i - 1
#                 while phrase[j] != ' ': #j ends on index of first whitespace before .com url
#                     j -= 1
#                 start = j + 1
#                 addUrl(phrase[start:end])
#     elif currChar == 'e':
#         incChar()
#         if currChar == 'd':
#             incChar()
#             if currChar == 'u':         #End of .edu url
#                 while currChar != ' ':  #End of file extention
#                     incChar()
#                 end = i
#                 j = i - 1
#                 while phrase[j] != ' ': #j ends on index of first whitespace before .edu url
#                     j -= 1
#                 start = j + 1
#                 addUrl(phrase[start:end])
#     elif currChar == 'g':
#         incChar()
#         if currChar == 'o':
#             incChar()
#             if currChar == 'v':         #End of .gov url
#                 while currChar != ' ':  #End of file extention
#                     incChar()
#                 end = i
#                 j = i - 1
#                 while phrase[j] != ' ': #j ends on index of first whitespace before .gov url
#                     j -= 1
#                 start = j + 1
#                 addUrl(phrase[start:end])
#     elif currChar == 'n':
#         incChar()
#         if currChar == 'e':
#             incChar()
#             if currChar == 't':         #End of .net url
#                 while currChar != ' ':  #End of file extention
#                     incChar()
#                 end = i
#                 j = i - 1
#                 while phrase[j] != ' ': #j ends on index of first whitespace before .net url
#                     j -= 1
#                 start = j + 1
#                 addUrl(phrase[start:end])
#     elif currChar == 'o':
#         incChar()
#         if currChar == 'r':
#             incChar()
#             if currChar == 'g':         #End of .org url
#                 while currChar != ' ':  #End of file extention
#                     incChar()
#                 end = i
#                 j = i - 1
#                 while phrase[j] != ' ': #j ends on index of first whitespace before .org url
#                     j -= 1
#                 start = j + 1
#                 addUrl(phrase[start:end])
#     else:
#         aCase()

# def zCase():
#     incChar()
#     if i >= len(phrase) - 1:
#         True
#     elif currChar == ' ':
#         bCase()
#     else:
#         zCase()

urls = find_ip()
while i < len(urls):
    print(urls[i])
    i += 1
