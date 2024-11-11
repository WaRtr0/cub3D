#!/bin/bash

# Sauvegarde le temps de départ en microsecondes
start=$(date +%s%N)

# Execute le programme
$@

# Sauvegarde le temps de fin en microsecondes
end=$(date +%s%N)

# Calcule la différence en microsecondes
runtime=$(( (end-start)/1000000 ))

# Affiche le résultat
echo "Temps d'execution: $runtime millisecondes"