// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VillainPlayerState.h"

AVillainPlayerState::AVillainPlayerState()
{
	// How often the server will try to update clients. Lyra & Fortnite use about 100.f as well. 
	NetUpdateFrequency = 100.f;
}
