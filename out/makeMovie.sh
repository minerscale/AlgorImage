#!/usr/bin/env bash

echo "Generating the frames..."
./algorimage
echo "Sticking them together..."
ffmpeg -y -loglevel panic -r 60 -i frames/frame_%d.png -vcodec libx264 -crf 0 -pix_fmt yuv420p movie.mp4
