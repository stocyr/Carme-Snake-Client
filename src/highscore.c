/*****************************************************************************/
/*  Modul      :   Highscore                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Vergleicht neuen Score, mit topten und ordned neuen score */
/* 				   in den TopTen passend ein. Lädt TopTen aus Datei und      */
/*				   speichert neue Liste wieder in der Datei					 */
/*                                                                           */
/*  Bearbeiter :   D.Robellaz                                                */
/*                                                                           */
/*  History    :   30.03.2012 robed1 erstellt                                */
/*				   17.12.2012 ambup1 Kopiert von Tequiz-Spiel, Totalüber-	 */
/*							         arbeitung und Anpassung an Carme-Snake	 */
/*                                                                           */
/*  File Name  :   highscore.c                                               */
/*                                                                           */
/*****************************************************************************/

/**
 *  \file highscore.c
 *  Modul zum Handling des Scores und der Highscoreliste.
 */

//Header Dateien implementieren
#include "highscore.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************/
/*  Funktion   :   Highscore                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Wertet Scores aus und vergleicht sie						 */
/*                                                                           */
/*  Bearbeiter :   D.Robellaz                                                */
/*                                                                           */
/*  History    :   04.04.2012 robed1 Erstellt                                */
/*				   17.12.2012 ambup1 Kopiert von Tequiz-Spiel, Totalüber-	 */
/*							         arbeitung und Anpassung an Carme-Snake	 */
/*                                                                           */
/*****************************************************************************/

/**
 * Handling der Highscorefunktionen und prüfen ob Highscore geknackt wurde
 * @param name zeigt auf Array mit dem Spielernamen
 * @param score enthält den erreichten score im aktuellen Spiel
 * @param ApplicationPath zeigt auf den Pfad des Spiels
 * @return Gibt 1 zurück wenn der Highscore geknackt wurde, sonst 0
 */

int highscore(char *name, int score, const char *ApplicationPath)
{
	// Funktion fileload aufrufen
	fileload(ApplicationPath,topten);

	// im 11. (leeren) Eintrag des Arrays den Aktuellen Spieler einfuegen
	strcpy(topten[10].name, name);
	topten[10].score = score;

	// Funktion sort aufrufen
	sort(topten);

	// Funktion filesave aufrufen
	filesave(ApplicationPath,topten);

	// Hat der aktuelle Spieler den Highscore geknackt?
	if (strcmp(topten[0].name,name)==0){
		if (topten[0].score == score){
			// Rueckgabe an Spiel-Modul
			return 1;
		}
	}
	// Rueckgabe an Spiel-Modul
	return 0;
}

/****************************************************************************/
/*	Ende Funktion highscore    												*/
/****************************************************************************/

/*****************************************************************************/
/*  Funktion   :   fileload                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Lädt das Highscore File und speichert die aktuellen Werte */
/*                 in einem Array ab.                                        */
/*                                                                           */
/*  Bearbeiter :   D.Robellaz                                                */
/*                                                                           */
/*  History    :   05.04.2012 Erstellt robed1                                */
/*				   17.12.2012 ambup1 Kopiert von Tequiz-Spiel				 */
/*                                                                           */
/*****************************************************************************/

/**
 * Lädt Highscoreliste aus Datei
 * @param Path zeigt auf den Pfad des Spiels
 * @param topten: Strukturarray mit geladener Highscoreliste
 */

void fileload (const char *Path, player topten[11]) {

	//Variablen definieren
	int i=0;
	char buffer[100];
	//Buffer für den Pfad des .txt
	char buffer2[1000];

	//Externes File definieren
	FILE *Highscore;

	//Kopiert den Pfad in Buffer
	strncpy(buffer2, Path, 950);

	//hängt Dateiname des .txt an den Pfad in Buffer
	strncat(buffer2, "\\highscore.txt", 48);

	//Externes File oeffnen
	Highscore = fopen(buffer2, "r");
	//Filepruefung
	if (Highscore != NULL) {
		//bis ans Ende des Files lesen
		while (!feof(Highscore)) {
			fgets(buffer, 99, Highscore);
			sscanf (buffer ,"%[^;];%d", topten[i].name, &topten[i].score);
			i++;
		}
	} else {
		//File konnte nicht geoeffnet werden
		printf ("Error: Die Datei konnte nicht geladen werden!\n");
	}
	//Externes File schliessen
	fclose(Highscore);
}

/****************************************************************************/
/*	Ende Funktion fileload     												*/
/****************************************************************************/

/*****************************************************************************/
/*  Funktion   :   filesave                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Speichert die aktuellen Werte in das Highscore File ab.   */
/*                                                                           */
/*  Bearbeiter :   D.Robellaz                                                */
/*                                                                           */
/*  History    :   06.04.2012 robed1 Erstellt                                */
/*				   17.12.2012 ambup1 Kopiert von Tequiz-Spiel				 */
/*                                                                           */
/*****************************************************************************/

/**
 * Speichert Highscoreliste in Datei
 * @param Path zeigt auf den Pfad des Spiels
 * @param topten: Strukturarray mit neuer Highscoreliste
 */

void filesave (const char *Path, player topten[11]){

	//Variablen definieren
	int i;
	//Buffer für den Pfad des .txt
	char buffer2[1000];

	//Externes File definieren
	FILE *Highscore;

	//Kopiert den Pfad in Buffer
	strncpy(buffer2, Path, 950);

	//hängt Dateiname des .txt an den Pfad in Buffer
	strncat(buffer2, "\\highscore.txt", 48);

	//Externes File oeffnen
	Highscore = fopen(buffer2, "w");

	//Filepruefung
	if (Highscore != NULL){
		for (i=0;i<10;i++){
			//neue Daten in das File schreiben
			fprintf(Highscore,"%s;%d\n",topten[i].name, topten[i].score);
		}

	} else {
		//File konnte nicht geoeffnet werden
		printf("Error: Datei konnte nicht gespeichert werden!\n");
	}
	//Externes File schliessen
	fclose(Highscore);
}

/****************************************************************************/
/*	Ende Funktion filesave     												*/
/****************************************************************************/

/*****************************************************************************/
/*  Funktion   :   sort                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :   Sortiert die Highscoredaten                               */
/*                                                                           */
/*  Bearbeiter :   D.Robellaz                                                */
/*                                                                           */
/*  History    :   06.04.2012 robed1 Erstellt                                */
/*				   17.12.2012 ambup1 Kopiert von Tequiz-Spiel				 */
/*                                                                           */
/*****************************************************************************/

/**
 * sortiert Highscoreliste absteigend nach Scores
 * @param topten: Strukturarray mit Highscoreliste
 */

void sort(player topten[11]){

	//Variablen definieren
	int i,n;

	//Temoraere Strucktur player definieren (wird zum kopiern verwendet)
	player temp;

	//erste for-Schlaufe des Bubble-Sort
	for (n=0;n<10;n++) {
		//zweite for-Schlaufe des Bubble-Sort
		for (i=0;i<10-n;i++){
			//vergleichen der verschiedenen scores (sortieren)
			if (topten[i].score<topten[i+1].score){
				temp = topten[i];
				topten[i] = topten[i+1];
				topten[i+1] = temp;
			}
		}
	}
	return;
}

/****************************************************************************/
/*	Ende Funktion sort      												*/
/****************************************************************************/



/*****************************************************************************/
/*  Ende Modul highscore                                       				 */
/*****************************************************************************/
