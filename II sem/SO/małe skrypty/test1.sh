#!/bin/bash

filename=''
directory=''
modification_time=''
file_size_operator=''  
file_size_value=''     
file_owner=''
file_content=''

while [ "$INPUT" != "8" ] 
do
    
    echo "1. Nazwa pliku: $filename"
    echo "2. Katalog: $directory"
    echo "3. Czas ostatniej modyfikacji: $modification_time"
    echo "4. Rozmiar (np. +1M, -100k): $file_size_operator$file_size_value"
    echo "5. Właściciel: $file_owner" 
    echo "6. Zawartość pliku: $file_content"
    echo "7. Szukaj"
    echo "8. Koniec"
    read INPUT

    if [ "$INPUT" = "1" ]; then
        echo "Podaj nazwę pliku:"
        read filename
    elif [ "$INPUT" = "2" ]; then
        echo "Podaj nazwę katalogu:"
        read directory
    elif [ "$INPUT" = "3" ]; then
        echo "Czas ostatniej modyfikacji (starsze niż):"
        read modification_time
    elif [ "$INPUT" = "4" ]; then
        echo "Podaj wartość rozmiaru "
        read file_size_value
    elif [ "$INPUT" = "5" ]; then
        echo "Właściciel:"
        read file_owner
    elif [ "$INPUT" = "6" ]; then
        echo "Zawartość pliku:"
        read file_content
    elif [ "$INPUT" = "7" ]; then
        find_command="find $directory "
        [[ ! -z $modification_time ]] && find_command+=" $modification_time"
        [[ ! -z $filename ]] && find_command+=" -name '$filename'"
        [[ ! -z $file_size_operator$file_size_value ]] && find_command+=" -size $file_size_value"
        [[ ! -z $file_owner ]] && find_command+=" -user $file_owner"
        [[ ! -z $file_content ]] && find_command+=" -exec grep -q '$file_content' {} \; -print"
        eval $find_command
        
        
    elif [ "$INPUT" = "8" ]; then
         exit 0
    fi
done
