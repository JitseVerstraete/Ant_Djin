CONTROLS:

movement: dpad or arrow keys:
aiming: Left and right bumper of comman & period keys
shooting: A-button or Right Alt



Engine Comments:


- Game Scenes	
	The game is split if up in game scenes, a scene contains game objects, which are updated, rendered... during the game loop. One scene can be active at the same time. GameObjects are created through a scene to ensure that every game object is part of a scene. 
	
- Game Loop:
	In the game loop all the game objects of a scene are "processed", every component of every game object gets updated, fixed-updated and rendered every frame.

	
- Component System:
	Components are the pattern that defines all of the functionality in the engine. Every component is part of a game object, and thus, is guaranteed to be updated every frame. Game objects have ownership over their components, and Scenes have ownership over their game objects, so this ensures that when the scene is destroyed, everything in it is also destroyed.
	

- Observer:
	There is an observer in the game that looks at player tank to see wether they killed enemy tanks. 

- Collision System:
	When creating a collider component, it is automatically added to the collision manager, where all colliders are compared agains one another, and when colliders overlap, A "OnCollision()" callback is called on the relevant game objects (and all their components)

- Transform:
	Transform is a mandatory "component" of a game object, it doesnt work like a real component, it uses the dirty flag pattern to make sure that the world transform (based on the transform of the parents) only get calculated when it is needed.
	
	

