#! /bin/bash
chmod +x "./cmake-build-debug/njvm"
chmod +x "/home/dev/KSP_public/aufgaben/a7/njvm"
for f in ./*.bin; do
    echo "origin $f"
    "/home/dev/KSP_public/aufgaben/a7/njvm" "$f"
    echo "njvm $f"
    "./cmake-build-debug/njvm" "$f"
done
