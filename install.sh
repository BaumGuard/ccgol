#!/bin/bash

scp src/ccgol /usr/bin

mkdir /usr/share/ccgol
mkdir /usr/share/ccgol/examples

scp share/ccgol.help /usr/share/ccgol
scp share/examples/glider_canon.gol /usr/share/ccgol/examples
