#!/bin/bash

# Author           : Filip Świniarski
# Created On       : 12.05.2024
# Last Modified By : s197725@student.pg.edu.pl
# Last Modified On : 16.05.2024
# Version          : v1.0
#
# Description      :
# Program służący do pakowania i rozpakowywania plików
# Dodatkowo istnieje opcja szyfrowania plików przy pakowaniu ( tar, tar.gz)
#
# Licensed under GPL (see /usr/share/common-licenses/GPL for more details
# or contact # the Free Software Foundation for a copy)

# Function to display help and version
show_help() {
    echo "Program służący do pakowania i rozpakowywania plików. Dodatkowo można szyfrować pliki przy pakowaniu do formatów .tar i .tar.gz"
}

show_version() {
    echo "Filip Świniarski v1.0"
}

# Handle -h and -v options
while getopts "hv" option; do
    case $option in
        h)
            show_help
            exit 0
            ;;
        v)
            show_version
            exit 0
            ;;
        *)
            echo "Unknown option"
            exit 1
            ;;
    esac
done

# Function to check if the file extension is supported
check_packed_file_extension() {
    local extension="${1##*.}"
    local supported_extensions=("tar" "tar.gz" "zip" "bz2")

    for ext in "${supported_extensions[@]}"; do
        if [ "$extension" == "$ext" ]; then
            echo "Supported :): $ext"
            return 0
        fi
    done
    echo "Not supported!: $extension"
    return 1  
}

# Function to show the main menu
show_main_menu() {
    local options=(
        "Pack File"
        "Unpack File"
        "Exit"
    )

    local dialog_options=()
    for i in "${!options[@]}"; do
        dialog_options+=("$((i+1))" "${options[$i]}")
    done

    dialog --backtitle "Menu" \
        --title "Choose your option" \
        --menu "Select one of the options below:" \
        15 60 4 \
        "${dialog_options[@]}" \
        2>/tmp/menuitem.$$
    
    menuitem=$(cat /tmp/menuitem.$$)
    clear
    rm /tmp/menuitem.$$
}

# Function to select a file
select_file() {
    FILE=$(dialog --stdout --title "Select a file" --fselect $HOME/Desktop/ 14 80)
}

# Function to select packing option
select_packing_option() {
    PACKING_OPTION=$(dialog --stdout --title "Select Packing Option" --menu "Choose a format" 15 60 4 \
        "tar" "tar" \
        "tar.gz" "tar.gz" \
        "zip" "zip" \
        "bzip2" "bzip2")
}

# Function to pack a file
pack_file() {
    while true; do
        select_file
        if [ -n "$FILE" ]; then
            select_packing_option
            filename=$(basename "$FILE")
            echo $filename
            case "$PACKING_OPTION" in
                "tar")
                    tar -cvf "${filename}.tar" "$FILE"
                    encrypt_file "${filename}.tar"
                    ;;
                "tar.gz")
                    tar -czvf "${filename}.tar.gz" "$FILE"
                    encrypt_file "${filename}.tar.gz"
                    ;;
                "zip")
                    zip "${filename}.zip" "$FILE"
                    echo "File has been packed to ${filename}.zip"
                    ;;
                "bzip2")
                    bzip2 -k "$FILE"
                    echo "File has been packed to ${FILE}.bz2"
                    ;;
                *)
                    dialog --msgbox "Not recognized option" 10 40
                    ;;
            esac
            handle_continue
        else
            dialog --msgbox "No file selected" 10 30
        fi
    done
}

# Function to encrypt a file
encrypt_file() {
    local file_to_encrypt=$1
    local passphrase=$(dialog --stdout --title "Enter a password" --passwordbox "Enter a password" 10 30)
    gpg --batch --yes --passphrase="$passphrase" -c "$file_to_encrypt"
    if [ $? -eq 0 ]; then
        dialog --msgbox "File has been encrypted!" 10 30
    else
        dialog --msgbox "Encryption failed. Please try again." 10 40
    fi
}

# Function to unpack a file
unpack_file() {
    while true; do
        select_file
        if [ -n "$FILE" ]; then
            filename=$(basename "$FILE")
            echo $filename
            extension="${FILE##*.}"
            case "$extension" in
                "tar")
                    tar -xf "$FILE" 
                    ;;
                "gz")
                    tar -xzf "$FILE"
                    ;;
                "zip")
                    unzip "$FILE"
                    ;;
                "bz2")
                    bunzip2 "$FILE"
                    ;;
                *)
                    dialog --msgbox "Unsupported file format: $extension" 10 40
                    ;;
            esac
            handle_continue
        else
            dialog --msgbox "No file selected" 10 30
        fi
    done
}

# Function to handle continuing or going back to menu
handle_continue() {
    dialog --backtitle "Choose option" \
        --title "Choose your next step" \
        --menu "Select one of the options below:" \
        15 60 2 \
        "Continue" "Continue" \
        "Menu" "Go to menu" \
        2>/tmp/continue.$$
    continue_option=$(cat /tmp/continue.$$)
    rm /tmp/continue.$$
    if [ "$continue_option" == "Menu" ]; then
        show_main_menu
    fi
}

# Main function
main() {
    while true; do
        show_main_menu
        case $menuitem in
            "1")
                pack_file        
                ;;
            "2")
                unpack_file
                ;;
            "3")
                exit 0
                ;;
            *)
                dialog --msgbox "Invalid option: $menuitem" 10 40
                ;;
        esac
    done
}

main

