#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include "EchiquierWidget.hpp"
#include "Fou.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "Echiquier.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include "mainWinUi.hpp"
#include <QPixmap>
#include <QLabel>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto &cdbg = clog;
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
    bibliotheque_cours::activerCouleursAnsi(); // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

    // cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.

    bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
#endif
    // NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::unique_ptr<Vue::MainWinUi> ui = std::make_unique<Vue::MainWinUi>();
    return app.exec();
}
