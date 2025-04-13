#ifndef LISTAS_H
#define LISTAS_H

#include "arquivos.h"

#define PLAYISTS_CSV "playlists.csv"
#define PLAYIST_CONTENTS_CSV "playlist_contents.csv"

typedef struct {
    char playlist_id[10];
    char nome[50];
    char user_id[10];
} Playlist;

void criarPlaylist(const char *user_id);
void gerenciarPlaylists(const char *user_id, CSVData *conteudos);
void mostrarPlaylistsUsuario(const char *user_id);

#endif