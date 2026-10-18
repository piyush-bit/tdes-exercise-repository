# lab-cpp-runner
# C++ language runner image for lab exercise evaluation.
# Based on gcc:13-bookworm.
# Provides g++ compiler, make, and bash so Makefile entrypoints work correctly during evaluation.

FROM gcc:13-bookworm
RUN apt-get update && apt-get install -y --no-install-recommends make bash && rm -rf /var/lib/apt/lists/*
