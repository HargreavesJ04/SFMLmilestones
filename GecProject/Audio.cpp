#include "Audio.h"

Audio::Audio()
{
}
//I love audio in sfml because its similar to graphics and its easy to infer what everything here does without documentation 

Audio::~Audio()
{
	StopMusic();

	for (auto& s : sound)
	{
		s.second->stop();
		delete s.second;
	}
	sound.clear();

	for (auto& b : buffer)
	{
		delete b.second;
	}
	buffer.clear();
}

bool Audio::LoadSound(const std::string& name, const std::string& filepath)
{
	sf::SoundBuffer* newBuffer = new sf::SoundBuffer();

	if (!newBuffer->loadFromFile(filepath))
	{
		delete newBuffer;
		return false;
	}

	buffer[name] = newBuffer;
	sound[name] = new sf::Sound(*buffer[name]);

	return true;
}

void Audio::PlaySound(const std::string& name)
{
	if (sound.find(name) != sound.end())
	{
		sound[name]->setLooping(false);
		sound[name]->play();
	}
}

void Audio::PlaySoundLooped(const std::string& name)
{
	if (sound.find(name) != sound.end())
	{
		if (sound[name]->getStatus() != sf::Sound::Status::Playing)
		{
			sound[name]->setLooping(true);
			sound[name]->play();
		}
	}
}

void Audio::StopSound(const std::string& name)
{
	if (sound.find(name) != sound.end())
	{
		sound[name]->stop();
	}
}

void Audio::PlayMusic(const std::string& filepath)
{
	if (music.openFromFile(filepath))
	{
		music.setLooping(true);
		music.play();
	}
}

void Audio::StopMusic()
{
	music.stop();
}

void Audio::SetMusicVolume(float volume)
{
	music.setVolume(volume);
}