#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>
#include <signal.h>
#include <pigpio.h>

#include "lib/Midi.h"

#include "Morceau.h"
#include "Piano.h"

using namespace std;
using namespace chrono;

#define baseIndex 	55 // 67
#define servosNumber 10

// Variable declaration
vector<int> mappingGPIO{12, 1, 16, 1, 23, 18, 1, 25, 1, 24}; 
vector<int> mappingInv{0, 0, 1, 0, 1, 0, 0, 0, 0, 1}; 
Piano* piano;

char* path;
char* title;
char  silent = 0;

void stop(int signum) {
	for(auto it = mappingNoteGPIO.begin(); it != mappingNoteGPIO.end(); ++it) {
		servos[it - mappingNoteGPIO.begin()].Sleep();
	}	
}

int main(int argc, char *argv[]) {
	if (argc < 3 || argc > 4) {
		cerr << "At least two arguments are required. Maximum three arguments. \n" << endl;
		cerr << "Usage: sudo ./a.out song_name file.mid [silent] \n" << endl;
		exit(1);
	}
	if (argc == 4) {
        if(strcmp(argv[3], "silent") == 0)
		    cout << "Silent mode activated." << endl;
        else
            cout << "Wrong option: " << argv[3] << ", should be \"silent\"." << endl;
            exit(1);
	}

	title = argv[1];
	path = argv[2];

    piano = new Piano(mappingGPIO, mappingInv, baseIndex);
	if(!silent) cout << piano;

	// ====================================
	// 				Music tiem
	// ====================================

	char n;
	Morceau morceau(title, path);
	if(!silent) cout << morceau;

	auto& tracks = morceau.getTracks();
	cout << "\nSelect track (" << morceau.getHeader().getNTracks() << " available(s)):" << endl;
    int track_id;
    cin >> track_id;
    const auto track = tracks[track_id];
	auto& events = track.getEvents();
    auto last = high_resolution_clock::now();

    for(const auto& trackEvent : events) {
        auto* event = trackEvent.getEvent();
        while((long)duration_cast<milliseconds>(high_resolution_clock::now()-last).count() < morceau.getTiming(trackEvent)) {}
        last = high_resolution_clock::now();
        if(event->getType() == MidiType::EventType::MidiEvent) {
            auto* midiEvent = (MidiEvent*)event;
            cout << "		Midi event:" << endl;
            auto status = midiEvent->getStatus();

            if(status == MidiType::MidiMessageStatus::NoteOn) {		// Note ON -> Play corresponding GPIO
                n = (char)midiEvent->getNote();
                if(midiEvent->getVelocity()) {
                    p[n].noteOn();
                    gpioSleep(PI_TIME_RELATIVE, 0, 10);
                } else {
                    p[n].noteOff();
                    gpioSleep(PI_TIME_RELATIVE, 0, 200000);
                }
            }
        if(!silent) morceau.getNoteInformation(midiEvent, trackEvent);
        }
	}

	gpioTerminate();
	return 0;
}
