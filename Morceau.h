#ifndef MORCEAU_H
#define MORCEAU_H
#include <string>
#include <cstring>
#include <iostream>
#include "lib/Midi.h"
using namespace std;

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


class Morceau : public Midi {
    private:
        char* Titre;
        char* Path;

    public:
        Morceau();
        Morceau(char* Titre, char* Path);
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