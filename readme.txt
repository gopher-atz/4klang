-----------------------------------------
first things first (info and legal stuff)
-----------------------------------------

4klang is a modular software synthesizer intended to be used in 4k intros.
you are free to use it in your 4k intros if you give proper credits.

the vsti plugin allows you to basically use any host application you like for composing a song. just put the 4klang.dll in the plugins folder or let some path point to its location.
please note 4klang is a 32bit vsti and needs a 32bit host to run.
4klang will output a c header file (.h) and the assembler source of the synth including the player and the song (.asm .inc) which you can compile to your executable, so including it is quite easy.
the examples are for demonstration purpose and not exactly a real world (aka 4k) scenario. especially they still link the 4klang.obj directly instead of compiling the 4klang.asm and 4klang.inc directly, but you should be able to figure that one out :)
i didnt include a seperate osx project as i dont have osx available, but i was reported the linux example should work without much hassle.
4klang is provided as is. reporting bugs/requests and general feedback is appreciated but changes depend on my time and mood :)

if you feel like sharing some intruments/songs you created with 4klang (after you used it), feel free to contact us (email at the bottom) we'd like to extend the examples.

since version 3.0 the source code package is available. so if you want to see the inner workings (assembler), the ugly vsti plugin code(c/c++) or simply really dare to compile it yourself or modify it fell free to do so now.

--------------
Using the VSTi 
--------------

the basic principle behind the 4klang synthesizer is a signal stack.

each unit you add at a certain slot will work with the signals that were put on the stack before. there's no need to put the units directly after each other though, empty slots will just pass through the current signal stack.

available units are:
- envelope     - a simple adsr envelope. puts a signal on the stack
- oscillator   - the basic sound generating unit (with additional lfo option) puts a signal on the stack. it has a builtin shaping function whith behaves just like the distortion shaper below. also it now has a gate waveform which can be controlled via the bitpattern in the gui (osc signal will be 0 and 1 instead of -1 .. 1 with the other modes)
- filter       - a multimode filter for sound shaping. modifies the topmost signal on the stack.
- distortion   - a distortion unit. modifies the topmost signal on the stack.
- arithmetic   - performs basic arithmetic operations like adding signals... also able to add the topmost signal again on the stack (push) or remove the topmost signal (pop), or exchange the two topmost signals (XCHG), or load the current midi note value as normalized float (0..1). just have a look at the explanation in the unit window.
- store        - a storage command which routes the topmost signal to any unit in the local stack or to any other stack. this is your friend when it comes to modulations.
- panning      - this unit will take the topmost signal (mono) and make a stereo signal out of it (including panning)
- delay/reverb - a delay line / reverb unit. it takes the topmost signal and modifies it. has bpm sync and note sync capability (use note sync for karplus-strong like plucked strings) as well as an integrated lfo for chorus/flanger effect.
- output       - moves the stereo signal to the output buffers and optionally to the AUX buffer
- accumulate   - this unit can only be used in the global stack. it will accumulate the output or aux buffers from all instruments.
- load         - a unit which puts a value between -1 and 1 on the stack. also has a modulation capability so any store command can put its signal now directly on the stack.

the default instrument should give you a hint how a instrument should be built up.
if you want to have an audiable instrument you basically should not touch the last three units in the instrument stack (panning, delay/reberb, output). you can remove the delay/reverb though. in any case the signal count for an instrument MUST be 0 after the last unit.
if you use modulations, make sure that if they are generated with an own envelope or oscillator, that you remove the signal from the stack afterwards (via arithmetic->pop).
in the end its totally depending on what you want to do. e.g you could define an instrument which is not producing any sound itself but rather modulates some unit in some other instrument, in that case it will be a controll instrument. and since controll instruments dont need an output (since the signal is routed via the store unit) you dont need the panning, delay/reverb and output at the end. you only have to make sure you removed all signals from the stack after you stored the modulation signal somewhere. controll instruments are a bit tricky but mighty, since they give you the option to modulate a sound via triggering the controll instrument in its pattern.

the global stack behaves essentially just like an instrument stack, so you are free to use any stacking combination you like. just make sure that there's at least an accumulator for the output or the aux buffers somewhere (like in the default setting). the signal count in the global stack MUST be 0 after the last unit (output).

on the lower right you have the panic button, so in a case where you fucked up the sound/signal try pressing it :)
also in that corner is the polyphony combo box. basically each instrument in 4klang is monophone, but when setting the polyphony to 2 it allows you to have 1 note beeing in release mode (fading out) while the new one is playing already. the default setting of 1 should be quite ok. only set to 2 if you really need it (it doubles cpu usage, both at composing time as well as in the intro) 

please note that patches and instruments have to be loaded/saved manually. so if you load e.g a renoise song the VSTI plugin will show up but will only contain the default patch, therefore you have to load the corresponding patch for the song yourself.

4klang makes a backup of the current patch every 60 seconds. the backup file will be stored to c:\4klang.4kp. this file is also written when 4klang is shutdown by the host application. so in case you forgot to store your patch you have a chance it's not all lost :)

--------------------------------------
recording a song for use in a 4k intro
--------------------------------------

recording a song is quite easy. first make sure you have rewinded your song and that nothing is still playing (press panic to be sure).
then press the record button, afterwards start the song. when the song finished press stop and choose your destination path for the compiled .obj file.
for info on how to include the object file in your 4k take a look at the example code.
the options in the record section allow you to use different synth internal pattern sizes, different quantization, clipping of the final output, denormalization (preventing severe slowdown while processing) and enable the envelope and note recording option in the synth.
Additionally you may want the synth to output standard 16bit integer samples instead of floating point samples. Finally you have the option to let the object file be compiled in the linux ELF or OSX MACHO format (obviously only if you want to use it with a linux/osx binary).
envelope and note recording will be done when the sound is calculated in the intro and will give you access to those buffer so you can sync to the envelope level and current note of each instrument. for info on how to use that also refer to the example code.
PLEASE NOTE:
you need to have your VSTi host running at 44100hz, otherwise your recordings will be fucked up, since the synth will work ONLY at 44100hz in the intro
also any kind of effects like volume changes, ... and groove settings from the host wont be there in the actual 4k. so make sure you only hit notes and note offs while composing

-----------------------------
workflow and compression tips
-----------------------------

version 2.7 introduces a new file format, so instruments and patches created with it wont work in previous versions anymore (no need to keep an older 4klang.dll though).
but the 2.7 version will automatically convert older files to the current format. you'll be notified and advised to save it again with the current version when that happens.

version 3.0 also introduces a new file format to enable the new load unit. autoconvert again happens automagically
in fact without using the new load unit when saving the format is identical to the previous version except for the header bytes which are now '4k13' instead of '4k12'. so if you really need it in the previous version again a hexeditor is your friend.

you can load and save and reset the whole patch, the current selected instrument, and even a single unit. so a good way to work is creating a set of instruments / unit settings which can be reused often. 
also you can load instruments and patches (4ki and 4kp) via drag&drop into the 4klang gui.

when building instruments always have an eye on the signal count (numbers on the right side) and the last line in the instrument/global stack. if the signal stack is invalid (which means a unit doesnt have the correct number of inputs) it tells you at which unit that error occured.

only use units and as many units you really need. 4klang is really compact, but using 32 units per instrument will most probably give quite big files in the end.
the default values for the parameters usually are set to give the minumum code size (meaning they skip functionality), only exception here is the damping parameter in the delay line. setting that to 0 instead will lead to smaller object in the end.
same with the patch and song data. the more repetitive parameter values and the song itself are the smaller your file will be in the end.

apart from that, try understanding what each unit effectively does before doing really fancy stuff with ist :) start simple and get more complex over time (especially when doing cross modulations from one instrument to another).



for questions, bug reports, rants ... mail to: atz4klangATuntergrundDOTnet
or catch us on IRC (#atz on IRCNet)

updates will be available via:
- http://4klang.untergrund.net
- http://www.pouet.net/prod.php?which=53398

have fun!

(c) gopher&powl
alcatraz 2009
