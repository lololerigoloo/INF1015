
Instructions de compilation

Pour compiler et exécuter le projet, veuillez utiliser les commandes suivantes dans votre terminal :
mkdir build
cd build
cmake ..
make
./Echec

Note : Assurez-vous d'utiliser le fichier images.qrc afin que les chemins des ressources graphiques soient correctement reconnus par Qt.
Présentation du projet

Ce simulateur d'échecs permet de placer librement ses pièces sur l'échiquier, d'effacer les erreurs, de réinitialiser le plateau ou de lancer une partie complète.
Architecture technique

    Modèle (Namespace Modele) : Contient toute la logique métier.

        Hiérarchie de classes : La classe Piece est la classe parente de toutes les pièces (Roi, Reine, Fou, Cavalier, etc.). Chaque classe de pièce utilise un compteur statique pour gérer les instances.

        Gestion des déplacements : La classe DeplacementManager simule les coups à l'avance pour vérifier la légalité des mouvements, détecter les situations d'échec/échec et mat, et bloquer les coups illégaux.

        Règles spéciales : Le roque est supporté (conditionné par le fait que le Roi et la Tour n'aient jamais bougé). Les promotions de pions ne sont pas implémentées graphiquement pour simplifier l'interface MainWindow.

    Vue (Namespace Vue) : Chaque widget est encapsulé dans sa propre classe.

        Rendu graphique : L'échiquier est dessiné via l'événement paintEvent de Qt (similaire à une approche drawRect en Pygame). Les pièces sont affichées via des QPixmap.

        Gestion des widgets : L'interface inclut des labels dynamiques indiquant l'état de la partie (échec, échec et mat). Un effort particulier a été mis sur le redimensionnement (resizeEvent) pour adapter l'affichage malgré la complexité des widgets.

Fonctionnalités de fin de partie

Lorsqu'un échec et mat survient, les images des rois sont automatiquement modifiées : l'image du roi victorieux devient un trophée, et celle du roi vaincu change d'apparence.