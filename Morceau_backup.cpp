#include "Morceau_backup.h"

Morceaub::Morceaub() {
	this->Titre = nullptr;
	this->Path = nullptr;
	this->f = nullptr;
}

Morceaub::Morceaub(char* Titre, char* Path) {
	if (fs::path(Path).extension() != ".mid" || !fs::exists(Path)) {
		throw "Please provide a midi file. \n";
	}
	this->Titre = Titre;
	this->Path = Path;
}

void Morceaub::setTitre (char* Titre) {
	this->Titre = Titre;
}

void Morceaub::setPath (char* Path) {
	if (fs::path(Path).extension() != ".mid" || !fs::exists(Path)) {
		throw "Please provide a midi file. \n";
	}
	this->Path = Path;
	this->f = new Midi(this->Path);
}

char* Morceaub::getTitre() {
	return this->Titre;
}

char* Morceaub::getPath() {
	return this->Path;
}

Midi* Morceaub::getFile() {
	return this->f;
}

void Morceaub::getInformation() {
	auto& header = this->getFile()->getHeader();

	cout << "	Now playing " << this->getTitre()
	     << " from file " << this->getPath() << endl;
	cout << "File contents:" << endl;
	cout << "	Header:" << endl;
	cout << "		File format: " << (int)header.getFormat() <<
		 "\n		Number of tracks: " << header.getNTracks() <<
		 "\n		Time division: " << header.getDivision() << endl;
}

long Morceaub::getTiming(const MTrkEvent& tEvent) {
	return (long)(tEvent.getDeltaTime().getData())*(1000/(2*this->getFile()->getHeader().getDivision()));
}

void Morceaub::getNoteInformation(MidiEvent* midiEvent, const MTrkEvent& trackEvent) {
	auto status = midiEvent->getStatus();

	if (status == MidiType::MidiMessageStatus::NoteOn || status == MidiType::MidiMessageStatus::NoteOff) {
		cout << "\t\t\t" << "Note " << (midiEvent->getVelocity()? "on " : "off ")
		 << (int)midiEvent->getNote()
		 << " on channel " << (int)midiEvent->getChannel() << "\n";
	}
	cout << "\t\t\tLength: " << trackEvent.getDeltaTime().getData() << endl;
}