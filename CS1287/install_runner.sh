#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_TAG="lab-python-runner:v1.0"

echo "Building runner image '${IMAGE_TAG}' for CS1287..."
docker build -t "${IMAGE_TAG}" "${SCRIPT_DIR}"
echo "Successfully built runner image '${IMAGE_TAG}'."
