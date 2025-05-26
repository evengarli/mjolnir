#!/bin/bash

set -e
make
sudo make install
echo "Installation complete!"
echo "Use 'man mjolnir' to read the manual"
