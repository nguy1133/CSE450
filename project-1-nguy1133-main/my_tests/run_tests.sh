#!/usr/bin/env bash

# Run from the tests/ directory
BIN="../Project1"
EXPECTED_DIR="expected"
CURRENT_DIR="current"

mkdir -p "$CURRENT_DIR"

pass=0
fail=0

shopt -s nullglob
tests=( "$EXPECTED_DIR"/test-*.expected )
shopt -u nullglob

if (( ${#tests[@]} == 0 )); then
  echo "No expected files found in '$EXPECTED_DIR'."
  exit 1
fi

for exp in "${tests[@]}"; do
  base="${exp##*/}"              # e.g., test-00.expected
  id="${base%.expected}"         # e.g., test-00

  code_file="${id}.sstack"       # e.g., test-00.sstack (in this dir)
  out_file="${CURRENT_DIR}/${id}.current"
  status_file="${EXPECTED_DIR}/${id}.status"

  if [[ ! -x "$BIN" ]]; then
    echo "Missing executable: $BIN"
    exit 1
  fi
  if [[ ! -f "$code_file" ]]; then
    echo "Missing code file: $code_file"
    ((fail++))
    continue
  fi

  # Run Project1, capture BOTH stdout and stderr, and the exit code
  "$BIN" "$code_file" > "$out_file" 2>&1
  rc=$?

  # If you generated .status files when creating expected, verify exit code too.
  if [[ -f "$status_file" ]]; then
    expected_rc=$(tr -d '[:space:]' < "$status_file")
    if [[ "$rc" != "$expected_rc" ]]; then
      echo "$id ... Failed (exit $rc ≠ expected $expected_rc)"
      ((fail++))
      # Still check output difference to give more signal:
      if ! diff -q "$exp" "$out_file" > /dev/null; then
        echo "  Output differs as well."
      fi
      continue
    fi
  fi

  if ! diff -q "$exp" "$out_file" > /dev/null; then
    echo "$id ... Failed.  Diff:"
    diff -u "$exp" "$out_file" | sed -n '1,40p'
    ((fail++))
  else
    echo "$id ... Passed!"
    ((pass++))
  fi
done

total=$((pass + fail))
echo "Passed $pass of $total tests (Failed $fail)"
