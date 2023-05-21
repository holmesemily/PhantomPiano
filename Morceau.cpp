#include "Morceau.h"

Morceau::Morceau() : Midi(nullptr) {
	this->titre = nullptr;
	this->path = nullptr;
}

Morceau::Morceau(char* titre, char* path) : Midi(path) {
	this->titre = titre;
	this->path = path;
}

void Morceau::setTitre (char* titre) {
	this->titre = titre;
}

void Morceau::setPath (char* path) {
	if (fs::path(path).extension() != ".mid" || !fs::exists(path)) {
		throw "Please provide a midi file. \n";
	}
	Morceau newMorceau(this->titre, path);
	*this = newMorceau;
}

char* Morceau::getTitre() const {
	return this->titre;
}

char* Morceau::getPath() const {
	return this->path;
}

ostream& operator<< (ostream& os, const Morceau& m) {
	auto& header = m.getHeader();

	os << "Now playing " << m.getTitre()
	     << " from file " << m.getPath() << endl;
	os << "File contents:" << endl;
	os << "	Header:" << endl;
	os << "		File format: " << (int)header.getFormat() <<
		 "\n		Number of tracks: " << header.getNTracks() <<
		 "\n		Time division: " << header.getDivision() << endl;
    return os;
}

long Morceau::getTiming(const MTrkEvent& tEvent) const {
	return (long)(tEvent.getDeltaTime().getData())*(1000/(2*this->getHeader().getDivision()));
}

void Morceau::printNoteInformation(MidiEvent* midiEvent, const MTrkEvent& trackEvent) {
	auto status = midiEvent->getStatus();

	if (status == MidiType::MidiMessageStatus::NoteOn || status == MidiType::MidiMessageStatus::NoteOff) {
		cout << "\t\t\t" << "Note " << (midiEvent->getVelocity()? "on " : "off ")
		 << (int)midiEvent->getNote()
		 << " on channel " << (int)midiEvent->getChannel() << "\n";
	}
	cout << "\t\t\tLength: " << trackEvent.getDeltaTime().getData() << endl;
}
