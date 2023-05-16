#include "Morceau.h"

Morceau::Morceau() : Midi(nullptr) {
	this->Titre = nullptr;
	this->Path = nullptr;
}

Morceau::Morceau(char* Titre, char* Path) : Midi(Path) {
	this->Titre = Titre;
	this->Path = Path;
}

void Morceau::setTitre (char* Titre) {
	this->Titre = Titre;
}

void Morceau::setPath (char* Path) {
	if (fs::path(Path).extension() != ".mid" || !fs::exists(Path)) {
		throw "Please provide a midi file. \n";
	}
	Morceau newMorceau(this->Titre, Path);
	*this = newMorceau;
}

char* Morceau::getTitre() {
	return this->Titre;
}

char* Morceau::getPath() {
	return this->Path;
}

void Morceau::getInformation() {
	auto& header = this->getHeader();

	cout << "	Now playing " << this->getTitre()
	     << " from file " << this->getPath() << endl;
	cout << "File contents:" << endl;
	cout << "	Header:" << endl;
	cout << "		File format: " << (int)header.getFormat() <<
		 "\n		Number of tracks: " << header.getNTracks() <<
		 "\n		Time division: " << header.getDivision() << endl;
}

long Morceau::getTiming(const MTrkEvent& tEvent) {
	return (long)(tEvent.getDeltaTime().getData())*(1000/(2*this->getHeader().getDivision()));
}

void Morceau::getNoteInformation(MidiEvent* midiEvent, const MTrkEvent& trackEvent) {
	auto status = midiEvent->getStatus();

	if (status == MidiType::MidiMessageStatus::NoteOn || status == MidiType::MidiMessageStatus::NoteOff) {
		cout << "\t\t\t" << "Note " << (midiEvent->getVelocity()? "on " : "off ")
		 << (int)midiEvent->getNote()
		 << " on channel " << (int)midiEvent->getChannel() << "\n";
	}
	cout << "\t\t\tLength: " << trackEvent.getDeltaTime().getData() << endl;
}
