// --------------------------------------------------------------------------
// functions to shuffle playlists ~ JSt
// --------------------------------------------------------------------------
#pragma once

#include <vector>    // for std::vector
#include <optional>  // for std::optional

// demo struct for testing... create a real struct for tracks ASAP!
//struct track {
// int64_t track_id;
// int64_t album_id;
// int64_t artist_id;
//};
using track = std::string;
using album = std::vector<std::optional<track>>;
using albums = std::vector<album>;
// end demo structs



namespace shuffle {

using std::vector;


// -----------------------------------------------------------------
// shuffle a playlist by balancing ~ JSt
// -----------------------------------------------------------------
// concept for balanced_shuffle:
// - sort each album              | 1
// - find the largest album       | 2
// - insert dummys to spread all  | 3
//   other albums                 |
// - shuffle all albums again     | 4
// - all songs are now a table    |
//   with same length columns;    |
//   get songs from every column  | 5
// -----------------------------------------------------------------
albums balanced_shuffle(albums playlist);
// -----------------------------------------------------------------

// -----------------------------------------------------------------
// shuffle track by track with std algorithms ~ JSt
// -----------------------------------------------------------------
void simple_album_shuffle(album& single_album);
void simple_playlist_shuffle(albums& album_list);
}
