@echo off
REM Start the container (build if needed) and open an interactive shell.

cd /d "%~dp0"

echo Starting container...
docker compose up -d

echo Opening shell inside the container (type 'exit' to leave)...
docker compose exec student-env bash
