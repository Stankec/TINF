import charts
import re
import tkinter.filedialog
import subprocess
import sys


def print_statistics_dictionary(raw_dictionary, percentage_dictionary):
    print("---------------------\ncharacter: occurences")
    for key in raw_dictionary.keys():
        print("{}: {}".format(key, raw_dictionary[key]))
    print("\npercentages")
    for key in percentage_dictionary.keys():
        print("{}: {}%".format(key, percentage_dictionary[key]))
    print("---------------------")
    return


def output_dictionary(output_string):
    ##output_string = output.decode(encoding='ASCII')
    statistics = dict()

    for character in output_string:
        if character not in statistics.keys():
            statistics[character] = 0

        statistics[character] += 1

    return statistics


def raw_dictionary_to_percentages(raw_dictionary):
    number_of_chars = 0
    percentage_dictionary = dict()

    for number_of_occurences in raw_dictionary.values():
        number_of_chars += number_of_occurences

    for key in raw_dictionary.keys():
        percentage = (raw_dictionary[key] / number_of_chars) * 100
        percentage_dictionary[key] = percentage

    return percentage_dictionary

def divideStringIntoCouples(string, n):
    output_list = []
    for i in range(len(string) // n):
        temp_tuple = []
        for j in range(n):
            temp_tuple.append(string[n*i + j])
        temp_tuple = tuple(temp_tuple)
        output_list.append(tuple(temp_tuple))
    return output_list

percentages = list()

pathToExecutables = tkinter.filedialog.askopenfilenames(title="Odabir izvrsne datoteke automata")

while(len(pathToExecutables) != 4):
    print("odabrati tocno 4 izvorista! (npr i1.exe, i2.exe, i3.exe, i4.exe)")
    pathToExecutables = tkinter.filedialog.askopenfilenames(title="Odabir izvrsne datoteke automata")

razdioba = int(input("Unesi broj zdruzenih simbola: "))

for executablePath in pathToExecutables:
    machineOutput = subprocess.check_output(executablePath)
    machineOutput = machineOutput.decode(encoding='ASCII')
    machineOutput = divideStringIntoCouples(machineOutput, razdioba)

    outputOccurrences = output_dictionary(machineOutput)
    outputPercentages = raw_dictionary_to_percentages(outputOccurrences)
    print_statistics_dictionary(outputOccurrences, outputPercentages)
    percentages.append(outputPercentages)

moja_pita = charts.MakeMultipleCharts(2, 2, 0.1, 0.1, percentages)
moja_pita.render()
