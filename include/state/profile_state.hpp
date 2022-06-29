#pragma once

#include "profile.hpp"
#include "state.hpp"

class ProfileState : public State<ProfileState> {
public:
    ProfileState(ProfileService* profileService) :
        State<ProfileState>(), profileService(profileService) { }

    /**
   * @brief Set the current logged in AccountProfile
   *
   * @param profile new profile to set
   */
    void setCurrentProfile(SwitchProfile* profile);

    /**
   * @brief Get the current switch profile.
   *
   * @return current switch profile or the first profile if not found.
   */
    SwitchProfile* getCurrentProfile();

    ProfileService* operator->() { return profileService; }
    ProfileService& operator*() { return *profileService; }

private:
    SwitchProfile* currentProfile;
    ProfileService* profileService;
};