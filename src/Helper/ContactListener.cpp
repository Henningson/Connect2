#include "ContactListener.h"
#include "CircleEntity.h"

void ContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was a ball
	if (contact->GetFixtureA()->GetBody()->GetUserData() && contact->GetFixtureB()->GetBody()->GetUserData()) {
		static_cast<CircleEntity*>(contact->GetFixtureA()->GetBody()->GetUserData())->startContact();
		static_cast<CircleEntity*>(contact->GetFixtureB()->GetBody()->GetUserData())->startContact();
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	if (contact->GetFixtureA()->GetBody()->GetUserData() && contact->GetFixtureB()->GetBody()->GetUserData()) {
		static_cast<CircleEntity*>(contact->GetFixtureA()->GetBody()->GetUserData())->endContact();
		static_cast<CircleEntity*>(contact->GetFixtureB()->GetBody()->GetUserData())->endContact();
	}
}