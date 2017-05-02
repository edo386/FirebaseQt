#!/bin/bash

## Delete some keys that will not let the Pods install

# Fistr String: name = "Compile Sources";
# Second String: name = "Link Binary With Libraries";
# Third String: name = "Copy Bundle Resources";
file_name="$1"

sed -i '.old' '/name = \"Compile Sources\";/d' $file_name
sed -i '.old' '/name = \"Link Binary With Libraries\";/d' $file_name
sed -i '.old' '/name = "Copy Bundle Resources";/d' $file_name
