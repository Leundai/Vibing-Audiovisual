# Synthwave vibin

Author: Leonardo Galindo-Frias

---

My project will be an audio visualizer that is meant to be used in the background or simply want to distract yourself as a break. Primarily using frequency amplitudes to either spheres or some kind of visual that changes based on the decibels. Along with this I will implement Perlin Noise in order to create a natural-like terrain that will use specific characteristics of the song inputed. I am aiming at making this possible for multiple songs and not just a single one, which includes making a UI along with it as well.

For background knowledge, I don't have any experience with any of the topics previously spoken about along with Perlin Noise. And this is why I am highly motivated to learn more about these kinds of concepts in order to possibly apply them to future projects. This is also something I would likely be using during the weekends with friends. The simple fact of exposing myself to something new and not in my comfort zone makes it easier to go out of my way later on in the future to do new projects and sharpens my ability to learn new concepts quicker/better.

I am planning on using Simplex Noise which is a cinderblock as a primary source for my terrain generation. 
* https://github.com/simongeilfus/SimplexNoise
Along with this some audio handling in order to be able to analyze the music and at the same time play it easily.
* https://github.com/tmatma/Cinder-Audio2
Finally some kind of UI which I will be using specifically.
* Updated to using Cinder UI

The timeline within three weeks.

0. Get familiarized with cinder and the cinderblocks that I will be using. Reading through the documentation and get a general idea of how I will be setting up the UI with pretzle
1. Set up the file structure and begin by first implementing Simplex Noise as a 3D Terrain. Stretch goal for this week is to make it possible to make it visually appealing.
   * Similar to this video: https://www.youtube.com/watch?v=IKB1hWWedMk
2. Set up the audio visualizer which means analyzing the given song and mapping it to some visual object and also make the inputted song influence the Simplex Noise 3D terrain based on frequencies and amplitude.
3. Finish any kind of last minute fixes/Have a UI that can handle the given files.

Stretch Goals: 
* Add color to the 3D terrain that is also influenced by the music. Instead of it just influencing  the color of particles
* Create some kind of changing terrain that shifts while you trasverse it
* Improve the Audio Visualizer through more complex methods of changing colors
* Add different shapes that are influenced by the song
* Give options to instead remove the 3D terrain generator and choose their own objects that can be used as audio representations.
