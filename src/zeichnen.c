/*****************************************************************************/
/*  Modul      :   Zeichnen                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Zust�ndig f�r s�mtliche Anzeigen w�hrend des Spiel-       */
/*                 verlaufs.                                                 */
/*                                                                           */
/*  Bearbeiter :   M.Schl�ppi                                                */
/*                                                                           */
/*  History    :   18.03.2012 schlm19 erstellt                               */
/*				   25.12.2012 ambup1  Kopiert von Tequiz-Spiel, �berarbeitet */
/*									  und angepasst an Carme-Snake			 */
/*                                                                           */
/*  File Name  :   zeichnen.c                                                */
/*                                                                           */
/*****************************************************************************/

/* Files importieren */
#include "window.h"
#include "highscore.h"
#include "zeichnen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





/*****************************************************************************/
/*  Funktion   : Menu zeichnen	               	                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Erzeugt die Anzeigen des Hauptmenus.					     */
/*                                                                           */
/*  Bearbeiter : Marcel Schl�ppi                                             */
/*                                                                           */
/*  History    : 23.06.2012 schlm19 erstellt 						         */
/*				 26.12.2012 ambup1  Kopiert von Tequiz-Spiel, �berarbeitet   */
/*									und angepasst f�r Carme-Snake			 */
/*                                                                           */
/*****************************************************************************/

/**
 * Bildet das Menufenster auf dem Bildschirm ab.
 */

void Menu_zeichnen(void){
	/* Hauptmenu Anzeigen zeichnen */
	SelectFont("Bauhaus 93", 45, FONT_BOLD);
	DrawTextXY (800, 300, COL_BLUE, "CARME-SNAKE");
	SelectFont("Papyrus", 30, FONT_NORMAL);
	DrawTextXY (240, 230, COL_GREEN, "1 Spiel starten");
	DrawTextXY (236, 300, COL_LIGHTBLUE, "2 Hall of Fame");
	DrawTextXY (230, 370, COL_RED, "3 Spiel beenden");
	SelectFont("Agency FB", 16, FONT_NORMAL);
	DrawTextXY (600, 530, COL_LIGHTBLUE, "P. Amb�hl, M. B�rtschi, C. Stoller");
}


/*****************************************************************************/
/*  Funktion   : Highscore zeichnen                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   : Zeichnet die Highscoreliste.							     */
/*                                                                           */
/*  Bearbeiter : Marcel Schl�ppi                                             */
/*                                                                           */
/*  History    : 23.06.2012 schlm19 erstellt 						         */
/*				 26.12.2012 ambup1  Kopiert von Tequiz-Spiel und angepasst an*/
/*									Carme-Snake								 */
/*                                                                           */
/*****************************************************************************/

/**
 * Bildet die Highscoreliste auf dem Bildschirm ab.
 * @param *ApplicationPath ist Pointer auf den Pfad der ausf�hrbaren Datei
 */

void Highscore_zeichnen(const char *ApplicationPath){

	char Name[1];	///<Strukturarray mit einem Element um Fkt highscore() aufzurufen.
	Name[0]='a';
	int index;
	char ausgabe2[100];		///<Array um Punkte in Ziffern umzuwandeln

	highscore(Name, 1, ApplicationPath);
	ClearWindow ();

	SelectFont("Bauhaus 93", 30, FONT_BOLD);
	DrawTextXY (220, 50, COL_BLUE, "Highscoreliste");

	// Zeichnet die Highscoreliste
	SelectFont("Papyrus", 30, FONT_NORMAL);
	for(index=9; index>=0; index--){

		// Umwandlung der Punke

		sprintf(ausgabe2,"%d",topten[index].score);

		// Name und zugeh�rige Punkte darstellen

		DrawTextXY (50, 150+index*40, COL_LIGHTBLUE, topten[index].name);
		DrawTextXY (530, 150+index*40, COL_RED, ausgabe2);
	}
}

/****************************************************************************/
/*	Ende Funktion Highscore zeichnen    									*/
/****************************************************************************/

/*****************************************************************************/
/*  Ende Modul Zeichnen                                       				 */
/*****************************************************************************/
