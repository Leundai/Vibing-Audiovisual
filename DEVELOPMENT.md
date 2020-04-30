# Development

---
- **4/17/20** Figured out how to include Simplex Library
    - I still need to figure out how to include the pretzel ui cinderblock
    - However I have gotten great success after a decent amount of hours throughout the day!
    
- **4/18/20** Added PretzelUI library to project
    - Simple enough due to the case study that was given in the tutorial
    - Most of the battle for developing this project is finished so now its all about developing
    
- **4/19/20** Implemented Camera Perspective and 3D TriangleStrip View
    - Finally after following through a simplex noise tutorial I was able to follow a similar path of showing the strips
    - They are not noise influenced nor do they update yet how I would want them to for amplitudes

- **4/20/20** Dynamically changing Z Values for triangle strips with Noise!
    - Using the Simplex Noise and feeding it the x and y values of each block I was able to get some noise and map it
    - It looks very mountainous! At the same time it it finally one step closer to that of music visualizer
    - **TODO**
    - [x] Create the ability to put in a song and influence the noise values!
    - [x] Either real time process the music and update the audiovisual while playing or process it before playing
- **4/21/20** Implemented Changing Z Values based on Real Time Audio Analysis using DFT
    - Based on a threshold for the volume of the sound the audiovisual changes. However this only works for song that are very loud
    - Next on the list is to try to find a beat and only apply z values based on average loudness.
- **4/23/20** Learned more about shaders and also tweaked ranges of the audiovisual generation
    - The biggest challenge is just making this more visually appealing and being able to expand it to other songs
    - So the main thing that I will start to do is give two options, they can either upload their music or I'll just record their system.
- **4/26/20** Implemented functionality to load music from computer regardless of the location
    - This was just a simple lines of code however, the next thing that I want to do is include some kind of interface.
    IMgui seems to be the move. So I will go ahead and implement that! And we will be done with the project
    - Lastly just make the audio visualizer more appealing visually
- **4/29/20** Spheres have been added that are influenced by the specific frequency's amplitude
    - By making a star class this make it possible to easily make the multiple amount of stars object
    - If needed to place the stars randomly it can be done by providing a specific Vec3 space for x y and z
    - Colors are constant however so I still need to figure out how to it possible to be edited for people instead of going into the code