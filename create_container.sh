#!/usr/bin/env bash
# Start the container (build if needed) and open an interactive shell.

set -e

# Move to the directory where this script lives
cd "$(dirname "$0")"

# On Linux, allow the container to access the host X server
if [[ "$(uname)" == "Linux" ]]; then
    xhost +local:docker >/dev/null 2>&1 || true
fi

echo "Starting container..."
docker compose up -d

echo "Opening shell inside the container (type 'exit' to leave)..."
docker compose exec student-env bash
