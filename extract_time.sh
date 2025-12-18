#!/usr/bin/env bash
set -euo pipefail

OUT="roads_time.csv"

echo "N,k,time_ms" > "$OUT"

for out in testes/teste_*.out; do
  base=$(basename "$out" .out)        # teste_<N>
  N=${base#teste_}

  # Extract k from footer line: "K (arestas): <number>"
  k=$(grep -E 'M[[:space:]]*\(arestas\)[[:space:]]*:' "$out" \
      | grep -Eo '[0-9]+' | head -n 1 || true)

  # Extract time from footer line: "Tempo: <number> segundos"
  time_ms=$(grep -E 'Tempo[[:space:]]*:' "$out" \
      | grep -Eo '[0-9]+(\.[0-9]+)?' | head -n 1 || true)

  # Skip if missing
  if [[ -z "$k" || -z "$time_ms" ]]; then
    continue
  fi

  echo "$N,$k,$time_ms" >> "$OUT"
done

printf "CSV generated: %s\n" "$OUT"