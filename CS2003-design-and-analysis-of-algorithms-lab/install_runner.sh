#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMAGE_TAG="lab-cpp-runner:v1.0"

echo "Building runner image '${IMAGE_TAG}' for CS2003-design-and-analysis-of-algorithms-lab..."
docker build -t "${IMAGE_TAG}" "${SCRIPT_DIR}"
echo "Successfully built runner image '${IMAGE_TAG}'."
