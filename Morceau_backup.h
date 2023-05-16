#ifndef Morceau_backup_H
#define Morceau_backup_H
#include <string>
#include <cstring>
#include <iostream>
#include "lib/Midi.h"
using namespace std;

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


class Morceaub {
    private:
        char* Titre;
        char* Path;
        Midi* f;

    public:
        Morceaub();
        Morceaub(char* Titre, char* Path);
        void setTitre (char* Titre);
        void setPath (char* Path);
        char* getTitre();
        char* getPath();
        Midi* getFile();
        void getInformation();
        long getTiming(const MTrkEvent& tEvent);
        void getNoteInformation(MidiEvent* midiEvent, const MTrkEvent& trackEvent);
};

#endif