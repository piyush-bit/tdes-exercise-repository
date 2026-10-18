# lab-c-runner
# C language runner image for TOC lab exercise evaluation.
# Based on gcc:13-bookworm.

FROM gcc:13-bookworm
RUN apt-get update && apt-get install -y --no-install-recommends make bash && rm -rf /var/lib/apt/lists/*
