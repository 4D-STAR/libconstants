#!/bin/sh
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
fi
input_file="$1"
output_file="$2"
printf 'const char embeddedConstants[] = R"(' > "$output_file"
cat "$input_file" >> "$output_file"
printf ')";\n' >> "$output_file"
