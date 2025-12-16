#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>



class Audio
{
public: 

	Audio();
	~Audio();

	bool LoadSound(const std::string& name, const std::string& filepath);
	void PlaySound(const std::string& name);
	void PlaySoundLooped(const std::string& name);
	void StopSound(const std::string& name);

	void PlayMusic(const std::string& filepath);
	void StopMusic();
	void SetMusicVolume(float volume);

private: 

	std::unordered_map<std::string, sf::SoundBuffer*> buffer;
	std::unordered_map<std::string, sf::Sound*> sound;
	sf::Music music;

};

