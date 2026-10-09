#!/bin/python

import mystring


def main():
    #print(help(mystring))
    
    str1 = mystring.MyString("Hello ")
    str1 += "world"
    str2 = mystring.MyString("!")
    str1.append(str2)

    print(str1)


if __name__ == "__main__":
    main()
