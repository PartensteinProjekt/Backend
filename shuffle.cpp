// --------------------------------------------------------------------------
#include "shuffle.h"
// --------------------------------------------------------------------------
// stl
#include <random>    // for random_engine
#include <algorithm> // for std::shuffle
// non-stl
#include <range.h>   // for size_range{}


// --------------------------------------------------------------------------
albums shuffle::balanced_shuffle(albums original_playlist)
// --------------------------------------------------------------------------
{
    // 0 : edge case handling
    // ... for no elements
    if (original_playlist.empty()) {
        return {};
    }
    // ... for only one album
    if (original_playlist.size() == 1) {
        simple_album_shuffle(original_playlist[0]);
        return albums{ original_playlist };
    }

    // 1 : shuffle each album
    simple_playlist_shuffle(original_playlist);

    // 2 : find the largest album
    const auto max_size = std::max_element(std::begin(original_playlist), std::end(original_playlist), [](const album& a, const album& b) {
        return a.size() < b.size();
    })->size();

    // 3 : bring all albums to the same length by inserting dummy tracks
    for (auto& album : original_playlist) {
        while (album.size() < max_size) {
            album.push_back({/*dummy!*/});
        }
    }

    // 4 : shuffle all albums again
    simple_playlist_shuffle(original_playlist);

    // 5 : column select the virtual playlist table
    album balanced_list {};
    //for (size_t n = 0; n < max_size; ++n) {
    for (auto n : size_range{ 0, max_size }) {
        for (auto album : original_playlist) {
            const auto track = album[n];
            if (track) {
                balanced_list.push_back(track);
            }
        }
    }

    return albums{ balanced_list };
}

// --------------------------------------------------------------------------
void shuffle::simple_album_shuffle(album& single_album)
// --------------------------------------------------------------------------
{
    auto random_engine = std::default_random_engine{};
    std::shuffle(std::begin(single_album), std::end(single_album), random_engine);
}

// --------------------------------------------------------------------------
void shuffle::simple_playlist_shuffle(albums& album_list)
// --------------------------------------------------------------------------
{
    auto random_engine = std::default_random_engine{};
    for (auto& single_album : album_list) {
        std::shuffle(std::begin(single_album), std::end(single_album), random_engine);
    }
}