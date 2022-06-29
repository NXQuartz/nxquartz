#include "state/profile_state.hpp"

void ProfileState::setCurrentProfile(SwitchProfile* profile) {
	this->currentProfile = profile;
	dispatchUpdate();
}

SwitchProfile* ProfileState::getCurrentProfile() {
	if (currentProfile != nullptr)
		return currentProfile;

    return profileService->getAll()[0];
}