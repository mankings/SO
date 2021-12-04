#!/bin/bash

#declare variables and arrays
declare -a IFACES
declare -a DATA
declare -a T
declare -a R
declare -a T0
declare -a R0
declare -a T1
declare -a R1
declare -a T2
declare -a R2
declare -a RTOT
declare -a TTOT
declare -a LINES
declare -a SORTEDLINES
declare -a FILTEREDLINES
declare -a TEMP

#functions
usage() { echo "Usage: $0 [-c interfaces] [-b | -k | -m] [-p n] [-t | -r | -T | -R] [-v] [-l loopTime] seconds" 1>&2; exit 1; }

sortTable() {
    [ -z "$OP_L" ] && for (( i=0; i<${#IFACES[@]}; i++ )); do #convert to lines for sorting
        printf -v LINES[$i] "%s %s %s %s %s" "${IFACES[$i]}" "${T[$i]}" "${R[$i]}" "${TR[$i]}" "${RR[$i]}"
    done

    [ ! -z "$OP_L" ] && for (( i=0; i<${#IFACES[@]}; i++ )); do #convert to lines for sorting
        printf -v LINES[$i] "%s %s %s %s %s %s %s" "${IFACES[$i]}" "${T[$i]}" "${R[$i]}" "${TR[$i]}" "${RR[$i]}" "${TTOT[$i]}" "${RTOT[$i]}"
    done

    case $SORT in
        "t")
            { [ -z "$OP_V" ] && mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k2 -n ); } || mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k2 -n -r )
            ;;
        "r")
            { [ -z "$OP_V" ] && mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k3 -n ); } || mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k3 -n -r )
            ;;
        "T")
            { [ -z "$OP_V" ] && mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k4 -n ); } || mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k4 -n -r )
            ;;
        "R")
            { [ -z "$OP_V" ] && mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k5 -n ); } || mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" | sort -k5 -n -r )
            ;;
        *)
            mapfile -t SORTEDLINES < <( printf "%s\n" "${LINES[@]}" )
            ;;
    esac
}

filterTable() {
    count=0
    for (( i=0; i<${#SORTEDLINES[@]}; i++ )); do
        TEMP=(${SORTEDLINES[$i]})
        if [[ "${TEMP[0]}" == *"$OP_C"* ]]; then
            FILTEREDLINES[$count]=${SORTEDLINES[$i]}
            count=$(( $count + 1 ))
        fi
    done
}



format="%-13s%10s%10s%10s%10s\n"
formatExtended="%-13s%10s%10s%10s%10s%10s%10s\n"

printTable() {
    sortTable
    filterTable
    printf "$format" "NETIF" "TX" "RX" "TRATE" "RRATE"
    for (( i=0; i<$INTNO; i++ )); do
        TEMP=(${FILTEREDLINES[$i]})
        printf "$format" "${TEMP[0]}" "${TEMP[1]}" "${TEMP[2]}" "${TEMP[3]}" "${TEMP[4]}"
    done
}

printTableLoop() {
    sortTable
    filterTable
    printf "$formatExtended" "NETIF" "TX" "RX" "TRATE" "RRATE" "TXTOT" "RXTOT"
    for (( i=0; i<$INTNO; i++ )); do
        TEMP=(${FILTEREDLINES[$i]})
        printf "$formatExtended" "${TEMP[0]}" "${TEMP[1]}" "${TEMP[2]}" "${TEMP[3]}" "${TEMP[4]}" "${TEMP[5]}" "${TEMP[6]}"
    done
}

# argument parsing
while getopts "c:bkmp:trTRvl" arg; do
    case $arg in
        c)
            OP_C=$OPTARG
            ;;
        b)
            OP_B=1
            ;;
        k)
            OP_K=1
            ;;
        m)
            OP_M=1
            ;;
        p)
            OP_P=$OPTARG
            ;;
        t)
            OP_T=1
            SORT="t"
            ;;
        r)
            OP_R=1
            SORT="r"
            ;;
        T)
            OP_TR=1
            SORT="T"
            ;;
        R)
            OP_RR=1
            SORT="R"
            ;;
        v)
            OP_V=1
            ;;
        l)
            OP_L=1
            ;;
        *)
            usage
            exit 0
            ;;
    esac
done
shift $((OPTIND-1))
seconds=$@

if [ $(( OP_B + OP_K + OP_M )) -eq 0 ]; then
    OP_B=1
elif [ $(( OP_B + OP_K + OP_M )) -gt 1 ]; then
    echo "ERROR: Mutually exclusive arguments specified."
    usage
    exit 0
fi

if [ $(( OP_T + OP_R + OP_TR + OP_RR )) -gt 1 ]; then
    echo "ERROR: Mutually exclusive arguments specified."
    usage
    exit 0
fi

if [ $(($seconds)) -le 0 ]; then
    echo "ERROR: Invalid seconds value."
    usage
    exit 0
fi


#fetching the values
IFACES=($(ifconfig -a | cut -d ' ' -f1 | tr ':' '\n' | awk NF))

INTNO=${#IFACES[@]} #process -p option
[ ! -z "$OP_P" ] && [[ $OP_P -lt ${#IFACES[@]} ]] && INTNO="$OP_P"

DATA=($(ifconfig -a | grep "packets" | awk '{print $5}'))
for ((i=0; i<${#IFACES[@]}; i++)); do
    T0[$i]="${DATA[$(($((2*i))+1))]}"
    R0[$i]="${DATA[$((2*i))]}"
    T1[$i]="${T0[$i]}"
    R1[$i]="${R0[$i]}"
done

while : ; do #do-while loop
    sleep $seconds

    DATA=($(ifconfig -a | grep "packets" | awk '{print $5}'))
    for (( i=0; i<${#IFACES[@]}; i++ )); do
        T2[$i]="${DATA[$(($((2*i))+1))]}"
        R2[$i]="${DATA[$((2*i))]}"
    done

    #process DATA
    for (( i=0; i<${#IFACES[@]}; i++ )); do
        T[$i]=`echo "${T2[$i]}-${T1[$i]}" | bc`
        R[$i]=`echo "${R2[$i]}-${R1[$i]}" | bc`
    done

    if [[ "$OP_K" -eq 1 ]]; then #convert into kb
        for (( i=0; i<${#IFACES[@]}; i++ )); do
            T[$i]=`echo "scale=1; ${T[$i]}/1024" | bc`
            R[$i]=`echo "scale=1; ${R[$i]}/1024" | bc`
        done
    fi

    if [[ "$OP_M" -eq 1 ]]; then #convert into mb
        for (( i=0; i<${#IFACES[@]}; i++ )); do
            T[$i]=`echo "scale=1; ${T[$i]}/1048576" | bc`
            R[$i]=`echo "scale=1; ${R[$i]}/1048576" | bc`
        done
    fi

    for (( i=0; i<${#IFACES[@]}; i++ )); do #get rates
        TR[$i]=`echo "scale=1; ${T[$i]}/$seconds" | bc`
        RR[$i]=`echo "scale=1; ${R[$i]}/$seconds" | bc`
    done

[ ! -z "$OP_L" ] || { printTable && break; } #check for do-while

    for (( i=0; i<${#IFACES[@]}; i++ )); do
        T1[$i]="${T2[$i]}"
        R1[$i]="${R2[$i]}"
        TTOT[$i]=`echo "${T1[$i]}-${T0[$i]}" | bc`
        RTOT[$i]=`echo "${R1[$i]}-${R0[$i]}" | bc`
    done

    if [[ "$OP_K" -eq 1 ]]; then #convert into kb
        for (( i=0; i<${#IFACES[@]}; i++ )); do
            TTOT[$i]=`echo "scale=1; ${TTOT[$i]}/1024" | bc`
            RTOT[$i]=`echo "scale=1; ${RTOT[$i]}/1024" | bc`
        done
    fi

    if [[ "$OP_M" -eq 1 ]]; then #convert into mb
        for (( i=0; i<${#IFACES[@]}; i++ )); do
            TTOT[$i]=`echo "scale=1; ${TTOT[$i]}/1048576" | bc`
            RTOT[$i]=`echo "scale=1; ${RTOT[$i]}/1048576" | bc`
        done
    fi

    printTableLoop && echo
done