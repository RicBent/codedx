# codedx
codedx allows compiling code for 32 bit Nintendo Switch games and hooking into them. The headers and code in this repository are targetted at New Super Mario Bros. U Deluxe but in theory the build system should work with all 32 bit switch games.

This build system was developed to be very easily and quick to use. With a single command you can compile, link, create the hooks and upload everything to your console ready for testing! There are multiple tools contained in this which can all be used on their own, but the entire build process is automated with dxmake.py.

The build system is written in python and currently runs on Linux only because the mangler library used does not run anywhere else. This shouldn't be difficult to modify though.

This code was intended for a larger mod of NSMBUDX which sadly did not see enough progress and thus I ceased development. I am releasing this hoping that it will be useful to somebody else.

### Game headers for
* Basic types like vectors and matrices
* Basic course actors (Actor/StageActor/CollisionActor/MultiStateActor/Enemy/BroBase)
* Colliders
* Collision Manager
* Particle Effects
* Course events
* Lights
* Line Followers
* Reveal Masks
* (Animated) 3d Models
* Linked movement handlers
* Parts of the nn and sead libraries
* More

### Custom actors and enemies
* Effect spwaner
* Fake Star Coin
* Light Actor
* "Magic Lift"
* Angry Sun/Mad Moon

### Misc.
* Reimplementation of the profile system that allows an arbitrary number of actors
* romfs and save data redirection to to the sd card
* Logging over a network connection
* A custom exception handler that shows detailed crash messages (uses network logging)
