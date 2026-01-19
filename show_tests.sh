#!/bin/bash
ANSI_FILTER="s/\x1B\[(([0-9]{1,2})?(;)?([0-9]{1,2})?)?[m,K,H,f,J]//g"
while IFS= read -r line; do
	FILE_WITH_LINE=$(echo $line | awk '{print $NF}')
	printf "%s\n" $FILE_WITH_LINE
	REMOVE_ANSI=$(echo $FILE_WITH_LINE | sed -r $ANSI_FILTER)
	FILE=$(echo $REMOVE_ANSI | cut -f 1 -d :)
	LINENUM=$(echo $REMOVE_ANSI | cut -f 2 -d :)
	sed -n "$LINENUM,/^$/p" "$FILE"
done < $1
