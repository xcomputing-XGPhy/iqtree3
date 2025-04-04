#!/bin/bash

ARCH=$(uname -m)
TMPDIR=$(mktemp -d)
BINARY=""

if [[ "$ARCH" == "x86_64" ]]; then
    BINARY="iqtree3_intel"
elif [[ "$ARCH" == "aarch64" ]]; then
    BINARY="iqtree3_arm"
else
    echo "Unsupported architecture: $ARCH"
    exit 1
fi

# Find the byte offset where the binary blob starts
M1="__BINARY"
M2="_START__"
MARKER="$M1$M2"
OFFSET=$(grep -a -b "$MARKER" "$0" | head -n1 | cut -d: -f1)
if [[ -z "$OFFSET" ]]; then
    echo "Binary marker not found."
    exit 1
fi

START_BYTE=$((OFFSET + ${#MARKER} + 2))

# Extract the tar.gz archive from the script and unpack
# Dump zip data to a temporary file
TMPZIP=$(mktemp)
tail -c +$START_BYTE "$0" > "$TMPZIP"

# Unzip the temporary file
unzip -o -q -d "$TMPDIR" "$TMPZIP"

# Clean up
rm -f "$TMPZIP"

# Run the extracted binary
"$TMPDIR/$BINARY" "$@"

# clean up
rm -rf "$TMPDIR"
exit
