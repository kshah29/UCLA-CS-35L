#!/usr/bin/python

# Kanisha shah
# 504-958-165 
# comm.py

import sys, random
from optparse import OptionParser
import argparse

if __name__ == "__main__":

        parser = argparse.ArgumentParser()

        """add argument functionality of ArgumentParser 
        parses options such as 1, 2, 3, u and i and stores 
        the boolean value in the mentioned dest variable"""
        parser.add_argument("-1", action="store_true", dest="col1")
        parser.add_argument("-2", action="store_true", dest="col2")
        parser.add_argument("-3", action="store_true", dest="col3")
        parser.add_argument("-u", action="store_true", dest="sort")
        parser.add_argument("-i", action="store_true", dest="icase")

        """options stores all the command line arguments except
        file1, file2 and comm.py """
        options = parser.parse_args(sys.argv[1:-2])
        
        """argv stores the list of all the command
        line arguments after parsing. Last and second
        last arguments are second and first file respectively"""
        file1 = sys.argv[-2]
        file2 = sys.argv[-1]

        """ We open file1, file2 and read the lines 
        from the files and store them in list 
        lines1 and lines2 if we are not receiving input from 
        standard input. If we are, we read from stdin"""
        if file1 == "-":
                lines1 = sys.stdin.readlines()
        else:
                f1 = open(file1, 'r')
                lines1 = f1.readlines()
                f1.close()

        if file2 == "-":
                lines2 = sys.stdin.readlines()
        else:
                f2 = open(file2, 'r')
                lines2 = f2.readlines()
                f2.close()


        """ sizeA and sizeB stores the length of the 
        lists lines1 and lines2 respectively """
        sizeA = len(lines1)
        sizeB = len(lines2)

        indexA = 0 #index of list lines1
        indexB = 0 #index of list lines2


        """In this while loop, as long as we haven't reached
        end of either lists we keep executing it. For 
        comparision and printing, if the last character of 
        the string is newline (\n), we remove it. This is done to 
        avoid the extra newline at the end of the string.
        We first check if option i was applied, if it
        was, we convert both the strings to lowercase
        for comparision. If 1st string is smaller than 
        2nd, we print the 1st one if option 1 is not used
        and move to the next value in the list lines1. Similarly, 
        when 2nd string is smaller, we print that string
        if option 2 is not used and move to the 
        next value in list lines2. If both the strings are 
        equal, we print the 1st one if option 3 is not used
        and move to the next value in both the strings. We add tabs 
        to the beginning of the string based on the options being
        printed. We only enter this loop, if option u is not passed."""
        while indexA < sizeA and  indexB < sizeB and not options.sort:
                #converts to lowercase for case insensitive comparision
                if options.icase :
                        #ignores newline character at the end
                        if (lines1[indexA])[-1] == "\n":
                                string1 = (lines1[indexA].lower())[0:-1]
                        else:
                                string1 = lines1[indexA].lower()
                        if (lines2[indexB])[-1] == "\n":
                                string2 = (lines2[indexB].lower())[0:-1]
                        else:
                                string2 = lines2[indexB].lower()
                #for case sensitive comparision
                else:
                        if (lines1[indexA])[-1] == "\n":
                                string1 = (lines1[indexA])[0:-1]
                        else:
                                string1 = lines1[indexA]
                        if (lines2[indexB])[-1] == "\n":
                                string2 = (lines2[indexB])[0:-1]
                        else:
                                string2 = lines2[indexB]


                if string1 < string2 :
                        #prints column 1 only if option 1 is not used
                        if not options.col1 :
                                if (lines1[indexA])[-1] == "\n":
                                        print((lines1[indexA])[0:-1])
                                else:
                                        print(lines1[indexA])
                        indexA = indexA + 1 #increments index in lines1
                        
                elif string1 > string2 :
                        #prints column 2 only if option 2 is not used
                        if not options.col2 :
                                #appends 1 tab in front if column 1 is printed
                                if not options.col1:
                                        lines2[indexB] = "\t" + lines2[indexB]

                                if (lines2[indexB])[-1] == "\n":
                                        print( (lines2[indexB])[0:-1])
                                else:
                                        print(lines2[indexB])
                        indexB = indexB + 1 #increments index in lines2
                        
                else : # string1 = string2
                        #prints column 3 only if option 3 is not used
                        if not options.col3 :
                                #appends 1 tab in front if only column 1 or 2 is printed
                                #appends 2 tabs in front if both column 1 and 2 are printed
                                if not options.col1 and not options.col2:
                                         lines1[indexA] = "\t\t" + lines1[indexA]
                                elif not options.col2: lines1[indexA] = "\t" + lines1[indexA]
                                elif not options.col1: lines1[indexA] = "\t" + lines1[indexA]
                                
                                if (lines1[indexA])[-1] == "\n":
                                        print((lines1[indexA])[0:-1])
                                else:
                                        print(lines1[indexA])
                        indexA = indexA + 1 #increments index in lines1
                        indexB = indexB + 1 #increments index in lines2


        """When option u is passed, it will compare each element in file1 to file2, 
        and print in column 1 if only in file1 and in column 3 if in both the files.
        The remaining elements of the file2 are printed then."""
        while indexA < sizeA and options.sort:

                found =	False #will keep track if the string found in both the files

                """iterates through every element in file2 and look for matches
                If a match is found, it sets the found value to true, deletes that 
                element from the list and decrements the size of lines2 by 1 """
                while indexB < sizeB:
                        #converts to lowercase for case insensitive comparision
                        if options.icase :
                        #ignores newline character at the end
                                if (lines1[indexA])[-1] == "\n":
                                        string1 = (lines1[indexA].lower())[0:-1]
                                else:
                                        string1 = lines1[indexA].lower()
                                if (lines2[indexB])[-1] == "\n":
                                        string2 = (lines2[indexB].lower())[0:-1]
                                else:
                                        string2 = lines2[indexB].lower()
                        #for case sensitive comparision
                        else:
                                if (lines1[indexA])[-1] == "\n":
                                        string1 = (lines1[indexA])[0:-1]
                                else:
                                        string1 = lines1[indexA]
                                if (lines2[indexB])[-1] == "\n":
                                        string2 = (lines2[indexB])[0:-1]
                                else:
                                        string2 = lines2[indexB]

                        #compares 2 strings to look for matches
                        if string1 == string2:
                                found = True
                                del lines2[indexB]
                                sizeB = sizeB - 1
                
                        indexB = indexB + 1
                        #inner while loop ends
                                
                #prints column 1 only if option 1 is not used
                if not found and not options.col1 :
                        if (lines1[indexA])[-1] == "\n":
                                print((lines1[indexA])[0:-1])
                        else:
                                print(lines1[indexA])
                                
                #prints column 3 only if option 3 is not used
                if found and not options.col3 :
                        #appends 1 tab in front if only column 1 or 2 is printed                      
                        #appends 2 tabs in front if both column 1 and 2 are printed                   
                        if not options.col1 and not options.col2:
                                lines1[indexA] = "\t\t" + lines1[indexA]
                        elif not options.col2: lines1[indexA] = "\t" + lines1[indexA]
                        elif not options.col1: lines1[indexA] = "\t" + lines1[indexA]

                        if (lines1[indexA])[-1] == "\n":
                                print((lines1[indexA])[0:-1])
                        else:
                                print(lines1[indexA])
                
                indexA = indexA + 1 #increments index in lines1
                indexB = 0 #sets indexB to 0 for next round 
                                
                
                        
        """If list2 has reached the end of the file, 
        we print the remaining values in list1 if 
        option 1 is not used"""
        while indexA < sizeA :
                if not options.col1:
                        if (lines1[indexA])[-1] == "\n":
                                print((lines1[indexA])[0:-1])
                        else:
                                print(lines1[indexA])
                indexA = indexA + 1 #increments index in lines1

        """If list1 has reached the end of the file,
        we print the remaining values in list2 if
        option 2 is not used"""
        while indexB < sizeB :
                if not options.col2:
                        if not options.col1:
                                lines2[indexB] = "\t" + lines2[indexB]
                        
                        if (lines2[indexB])[-1] == "\n":
                                print((lines2[indexB])[0:-1])
                        else:
                                print(lines2[indexB])
                indexB = indexB + 1 #increments index in lines2
        
		

