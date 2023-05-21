#ifndef MORCEAU_H
#define MORCEAU_H

#include <cstring>
#include <iostream>
#include <experimental/filesystem>

#include "lib/Midi.h"

using namespace std;
namespace fs = std::experimental::filesystem;

class Morceau : public Midi {
    private:
        char* titre;
        char* path;

    public:
        Morceau();
        Morceau(char* titre, char* path);
        void setTitre(char* titre);
        void setPath(char* path);
        char* getTitre();
        char* getPath();
        Midi* getFile();
        void printInformation();
        long getTiming(const MTrkEvent& tEvent);
        void printNoteInformation(MidiEvent* midiEvent, const MTrkEvent& trackEvent);
        friend ostream& operator<< (ostream& os, const Morceau& m);
};

#endif
