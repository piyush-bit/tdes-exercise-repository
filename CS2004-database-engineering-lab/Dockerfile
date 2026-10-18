# lab-sql-runner
# SQL/Database runner image for lab exercise evaluation.
# Based on python:3.11-slim.
# Provides python3, sqlite3, make, and bash so Makefile entrypoints work correctly during evaluation.

FROM python:3.11-slim
RUN apt-get update && apt-get install -y --no-install-recommends make bash sqlite3 && rm -rf /var/lib/apt/lists/*
