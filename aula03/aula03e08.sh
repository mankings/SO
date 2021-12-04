#!/bin/bash
# Select structure to create menus
PS3='Please select one of the options given: '

select option in $@; do
    case $REPLY in
        [1-$#])
        echo "You picked $option ($REPLY)." ;;
        *)
        echo "Invalid option. Exiting..."; break ;;
    esac 
done