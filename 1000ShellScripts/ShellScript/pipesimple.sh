#!/bin/bash

# Pipes directeaza iesirea unui program catre intrarea altui program

ls -l | sed -e "s/[aeio]/u/g"
