/*****************************************************************************/
/*  Modul      :  Header Highscore                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Funktion   :  Header-File zu highscore.c     							 */
/*				  															 */
/*  Bearbeiter :  Dominik Robellaz                                           */
/*                                                                           */
/*  History    :  30.03.2012 erstellt robed1                                 */
/*                                                                           */
/*  File Name  :  highscore.h                                                */
/*                                                                           */
/*****************************************************************************/

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

/* externe (globale) Funktionen */
///< Strukturarray für Highscoreliste
typedef struct {
	char name[100];
	int score;
} player;

extern int highscore(char *name, int score, const char *ApplicationPath);
extern void fileload (const char *Path, player topten[11]);

/* interne Funktionen */
void filesave (const char *Path, player topten[11]);
void sort(player topten[10]);

/* Array mit Struktur player und 11 Eintraege definieren */
player topten[11];	///<Strukturarray zum laden, bearbeiten und speichern der Highscoreliste

#endif
