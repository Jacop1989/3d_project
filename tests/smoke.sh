#!/bin/sh
set -e
if command -v timeout >/dev/null 2>&1; then
  timeout 1 ../build/3d_project >/dev/null 2>&1 || true
fi
