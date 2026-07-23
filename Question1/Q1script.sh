#!/bin/bash

SOURCE="submissions"
BACKUP="backup"
REPORT="report.txt"
ERRORS="errors.log"

mkdir -p "$BACKUP" 2>>"$ERRORS"

processed=0
duplicates=0
backedup=0

> "$REPORT"
> "$ERRORS"

declare -A files

for file in "$SOURCE"/*
do
    if [ -f "$file" ]; then
        processed=$((processed+1))

        hash=$(md5sum "$file" 2>>"$ERRORS" | cut -d' ' -f1)

        if [[ -z "${files[$hash]}" ]]; then
            files[$hash]=1
            cp "$file" "$BACKUP/" 2>>"$ERRORS"
            backedup=$((backedup+1))
        else
            duplicates=$((duplicates+1))
        fi
    fi
done

echo "Files Processed: $processed" >> "$REPORT"
echo "Duplicate Files: $duplicates" >> "$REPORT"
echo "Files Backed Up: $backedup" >> "$REPORT"

echo "Report Generated Successfully"
