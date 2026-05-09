#!/bin/bash
CWD="$(pwd)/Web/Integrated"

if [ ! -d "$CWD/node_modules" ]; then
	npm install
fi
npm run build
