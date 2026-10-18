#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Resolve euc2 binary location
EUC2_BIN=""
if [ -x "${REPO_ROOT}/euc2" ]; then
  EUC2_BIN="${REPO_ROOT}/euc2"
elif command -v euc2 >/dev/null 2>&1; then
  EUC2_BIN="$(command -v euc2)"
elif command -v tdes >/dev/null 2>&1; then
  EUC2_BIN="$(command -v tdes)"
else
  echo "Error: euc2 executable not found at ${REPO_ROOT}/euc2 or in PATH" >&2
  exit 1
fi

COURSE_NAME="$(basename "${SCRIPT_DIR}")"
echo "=========================================================="
echo " Packaging all exercises for ${COURSE_NAME} (skip-tests) "
echo "=========================================================="

success_count=0
fail_count=0

for dir in "${SCRIPT_DIR}"/*/; do
  if [ -f "${dir}manifest.json" ]; then
    lab_name="$(basename "${dir}")"
    echo -n "Packaging ${lab_name}... "
    if "${EUC2_BIN}" package "${dir}" --skip-tests "$@" >/dev/null 2>&1; then
      echo "DONE"
      success_count=$((success_count + 1))
    else
      echo "FAILED"
      "${EUC2_BIN}" package "${dir}" --skip-tests "$@" || true
      fail_count=$((fail_count + 1))
    fi
  fi
done

echo ""
echo "Summary for ${COURSE_NAME}: ${success_count} packaged successfully, ${fail_count} failed."
