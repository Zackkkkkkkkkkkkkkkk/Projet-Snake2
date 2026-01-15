#!/bin/bash
# Script pour créer un fichier carte.txt valide

cat > carte.txt << 'EOF'
10 15
###############
#             #
#             #
#   ###   ### #
#   # #   # # #
#   ###   ### #
#             #
#             #
#             #
###############
EOF

echo "Fichier carte.txt créé avec succès!"
echo ""
echo "Contenu du fichier :"
cat carte.txt
echo ""
echo "Vérification :"
wc -l carte.txt
ls -lh carte.txt
