#! /bin/bash
for f in ./*.nj; do
    /home/dev/KSP_public/aufgaben/a8/njc "$f" > "$(basename -- $f .nj).asm"
    # remember to quote it or spaces may misbehave
done

for f in ./*.asm; do
    echo "$f"
    /home/dev/KSP_public/aufgaben/a8/nja "$f" "$(basename -- $f .asm).bin"
    # remember to quote it or spaces may misbehave
done
