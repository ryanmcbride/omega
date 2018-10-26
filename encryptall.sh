#!/usr/bin/env bash
for filename in ./decrypted/*.*; do
    echo "$filename > ./omegalib/$(basename $filename)"
    ./bin/encrypt $(basename $filename) < ./decrypted/$(basename $filename) > ./omegalib/$(basename $filename)
done