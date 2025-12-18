#!/usr/bin/env bash
set -euo pipefail

GEN="./gerador_p2"
SOL="./a.out"

mkdir -p testes

for N in  900 1100 1300 1500 1700 1900 2100 2300 2500 2700 2900 3100 3300 3500 3700 3900 4100 4300; do
    "${GEN}" $N 100 50 > "testes/teste.in"
    "${SOL}" < "testes/teste.in" > "testes/teste_${N}.out"
done
