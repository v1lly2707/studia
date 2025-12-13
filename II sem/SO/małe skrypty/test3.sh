#!/bin/bash

filename=''
directory=''
modification_time=''
file_size_operator=''
file_size_value=''
file_owner=''
file_content=''

while true; do
    INPUT=$(dialog --menu "Wybierz opcję" 15 60 8 \
        1 "Nazwa pliku: $filename" \
        2 "Katalog: $directory" \
        3 "Czas ostatniej modyfikacji: $modification_time" \
        4 "Rozmiar (np. +1M, -100k): $file_size_operator$file_size_value" \
        5 "Właściciel: $file_owner" \
        6 "Zawartość pliku: $file_content" \
        7 "Szukaj" \
        8 "Koniec" \
        3>&1 1>&2 2>&3)

    if [ "$INPUT" = "1" ]; then
        filename=$(dialog --inputbox "Podaj nazwę pliku:" 8 60 "$filename" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "2" ]; then
        directory=$(dialog --inputbox "Podaj nazwę katalogu:" 8 60 "$directory" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "3" ]; then
        modification_time=$(dialog --inputbox "Czas ostatniej modyfikacji (starsze niż):" 8 60 "$modification_time" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "4" ]; then
        file_size_value=$(dialog --inputbox "Podaj wartość rozmiaru:" 8 60 "$file_size_value" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "5" ]; then
        file_owner=$(dialog --inputbox "Właściciel:" 8 60 "$file_owner" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "6" ]; then
        file_content=$(dialog --inputbox "Zawartość pliku:" 8 60 "$file_content" 3>&1 1>&2 2>&3)
    elif [ "$INPUT" = "7" ]; then
        find_command="find $directory "
        [[ ! -z $modification_time ]] && find_command+=" -mtime $modification_time"
        [[ ! -z $filename ]] && find_command+=" -name '$filename'"
        [[ ! -z $file_size_operator$file_size_value ]] && find_command+=" -size $file_size_value"
        [[ ! -z $file_owner ]] && find_command+=" -user $file_owner"
        [[ ! -z $file_content ]] && find_command+=" -exec grep -q '$file_content' {} \; -exec dialog --msgbox '{}' 8 60 \;"
        eval $find_command 
    elif [ "$INPUT" = "8" ]; then
         exit 0
    fi
done
