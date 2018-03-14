# 4klang
Official 4klang repository

Summary
-------

4klang is a modular software synthesizer package intended to easily produce music for 4k intros (small executables with a maximum filesize of 4096 bytes containing realtime audio and visuals).

It consists of a VSTi plugin example songs/instruments as well as an example C project showing how to include it in your code. 
Or if you dare to compile it yourself also the source code for the synth core and VSTi plugin.

The repository contains the folders:
- 4klang_VSTi (the precompiled plugin(s) and example instruments/songs)
- 4klang_source (the VSTi source as well as the needed 4klang.asm file for compilation in your exe)

The plugin project here is based on Visual Studio 2015, so that and above should compile out of the box.

![4klang image](https://raw.githubusercontent.com/hzdgopher/4klang/master/4klang.png)

Examples
--------

Some 4k intros using 4klang:

- http://www.pouet.net/prod.php?which=53937
- http://www.pouet.net/prod.php?which=68239
- http://www.pouet.net/prod.php?which=69642
- http://www.pouet.net/prod.php?which=69653

Goal
----

Up to now the 4klang package was available only via http://4klang.untergrund.net

Lately various subversions of 4klang emerged and i felt it might be a good idea to have a public repo reflecting that.
So people can actively contribute, fix things i dont have time for or simply extend stuff.

Therefore the current branches available here are:

- 3.0.1 (as listed on http://4klang.untergrund.net)
- 3.11 (as listed on http://4klang.untergrund.net)
- master (~3.2, contains various fixes and a new unit type 'glitch' for a delay based retrigger effect) 

History
-------

4klang development started in 2007 out of need and curiosity of how to write a tiny but flexible software synthesizer which can be used in 4k intros.

See this small writeup for more info
<br>http://zine.bitfellas.org/article.php?zine=14&id=35

Credits
-------

4klang was developed by
<br>Dominik Ries (gopher) and Paul Kraus (pOWL) of Alcatraz.

Among the many sources of inspiration which lead to 4klang in its current state, here is a (probably not complete) list of the most influencial work by others:

- <b>'Stoerfall Ost' by freestyle</b>

http://www.pouet.net/prod.php?which=743
<br>To my knowledge the first 4k intro using the fpu stack as 4klang does, creating the best 4k soundtrack of its time.
Conceptually i consider this to be the primary technological input as 4klang evolved around that idea of using the fpu stack.
So big respect and greetings to freestyle, particularly muhmac whom i also had some helpful discussions with during 4klang development.

- <b>V2 by kb of frabrausch</b>

http://www.pouet.net/prod.php?which=15073
<br>https://github.com/farbrausch/fr_public/tree/master/v2

Before 4klang i wrote my first synth as a V2 clone around 2004/2005 (as many people in the demoscene did actually).
Again way ahead of its time in terms of size/quality and in addition with some really helpful articles by kb this was a key to understanding what you need for synth development for a start:
<br>http://in4k.untergrund.net/various%20web%20articles/fr08snd1.htm
<br>http://in4k.untergrund.net/various%20web%20articles/fr08snd2.htm
<br>http://in4k.untergrund.net/various%20web%20articles/fr08snd3.htm
<br>http://in4k.untergrund.net/various%20web%20articles/fr08snd4.htm

- <b>http://www.musicdsp.org</b>

General source and for various synth module algorithms.
