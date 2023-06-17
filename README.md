<div align= >

# <img align=center width=75px height=75px src="https://media3.giphy.com/media/du476yhpPXCc1wIYcb/giphy.gif?cid=ecf05e47e39bqg60nvldbp9ucxb7m7d4g6lsmkylifj8136x&ep=v1_stickers_search&rid=giphy.gif&ct=s"> Frogger Game


</div>
<div align="center">
   <img align="center" width=498px height=260px src="https://media.tenor.com/I4J9Q3Aq0ZIAAAAC/frogger-cross-the-street.gif" alt="logo">

   ### ”Please, Help me to cross the road. 🐸“
</div>

<p align="center"> 
    <br> 
</p>

## <img align= center width=50px height=50px src="https://thumbs.gfycat.com/HeftyDescriptiveChimneyswift-size_restricted.gif"> Table of Contents

- <a href ="#about"> 📙 Overview</a>
- <a href ="#started"> 💻 Get Started</a>
- <a href ="#Path"> 🎯 Path of the program</a>
- <a href ="#structure"> 📁  File Structure</a>
-  <a href ="#video"> 📽 Demo</a>
- <a href ="#contributors"> ✨ Contributors</a>
- <a href ="#license"> 🔒 License</a>
<hr style="background-color: #4b4c60"></hr>

 <a id = "about"></a>

## <img align="center"  width =70px  height =70px src="https://media2.giphy.com/media/D8cXneB3lSI5nlPw6n/giphy.gif?cid=ecf05e47jaerq4hltuyo9rl0p3z56ts18smsai3uhoyjcklr&ep=v1_stickers_search&rid=giphy.gif&ct=s"> Overview
<br>
<ul> 
<li>
Frogger is the main character. Frogger need your help to cross the road. You should help him without make any accident.</li>
<li>The game satisfies requirements:
<ul>
<li>Usage of 3D models</li>
<li>Lighting with multiple lights in the scene</li>
<li>Texture mapping</li>
<li>A sky</li>
<li>3D motion.</li>
<li>Game logic</li>
<li>Scene Deserialization</li>
<li>Scene Serialization</li>
<li>Game logic</li>
<li>Scene Deserialization</li>
<li>Play state & Menu state & Game Over state</li>
</ul>
</li>
<li>3 types of Lighting
<ul>
<li>Spot</li>
<li>Directional</li>
<li>Point</li>
</ul>
</li>
<li>
You can view <a href="https://github.com/BasmaElhoseny01/frog-frenzy/blob/main/instructions.pdf">instructions</a> file
</li>
<li>
The project has 2 phases.</li>
<br>

 - <a href="https://github.com/BasmaElhoseny01/frog-frenzy/tree/a100eaaf89ac714deaee448e983b8fe676af1c9c">Project Phase 1</a>
 - <a href="https://github.com/BasmaElhoseny01/frog-frenzy">Project Phase 2</a>
<br>
<li> Build using <a href="https://docs.gl/">OpenGl 3</a> &&<a href="https://isocpp.org/"> C++ language</a> .</li>
</ul>
<hr style="background-color: #4b4c60"></hr>
<a id = "started"></a>

## <img  align= center width=60px height=50px src="https://media3.giphy.com/media/du476yhpPXCc1wIYcb/giphy.gif?cid=ecf05e47e39bqg60nvldbp9ucxb7m7d4g6lsmkylifj8136x&ep=v1_stickers_search&rid=giphy.gif&ct=s"> Get Started 

<ol>
<li>Clone the repository.

<br>

```
git clone https://github.com/BasmaElhoseny01/frog-frenzy
```

</li>
<li> You will need to download <a href="https://cmake.org/">CMake</a>. </li>
<br>
<li>  Install a C++ Compiler on if you haven't. Recommended (Visual Studio Community 2019 Release - amd64_x86).

<br>

```
.\bin\GAME_APPLICATION.exe\
```
</li>
</ol>
<hr style="background-color: #4b4c60"></hr>


## <img align= "center" width=80px height=80px src="https://media2.giphy.com/media/dAu3qBzpmXstCTimDv/giphy.gif?cid=ecf05e475rq4hwxg7usfm1go2dc1pl5gpbnvo1izu6ph4yuh&rid=giphy.gif&ct=s"> Path of the program <a id ="Path"></a>

<ol>
<li>When run the Project</li>
<br>
<table>
<tr>
<th align="center" width=70%>Image</th>
<th width=20%>Description </th>
</tr>
<tr>
<td align="center" ><img src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/e4415721-bcce-4508-a4cf-81e81d747213"></td>
<td>Main Menu you have 2 options
<ul>
<li>Press Space to start game</li>
<li>Press Esc to end game</li>
</ul>
</td>
</tr>
</table>
<li> When start Game, you can start playing.</li>
<br>
<div align="center">
<img width="500px" src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/7a949eda-0af2-4d9c-a3e1-679d48bd2427">
</div>

<br>
<li>Settings
<ul>
<li>Froward => W & 🔼</li>
<li>Left => A & ◀️</li>
<li>Right => D & ▶️</li>
<li>Speed => left shift</li>
<li>Exit Game => Esc</li>
</ul>
</li>
<li>Rules
<ul>
<li>You have at most 3 hearts. You start the game with 3 hearts.</li>
<li>If you make accident you loss one heart.</li>
<li>when you haven't any more hearts you die. </li>
<li>Score will increase by crossing the Road</li>
<li>Your goal is increasing score as you can</li>
</ul>
</li>
<li> When you die</li>
<br>
<table>
<tr>
<th align="center" width=70%>Image</th>
<th width=20%>Description </th>
</tr>
<tr>
<td align="center" ><img src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/8fcba191-6109-41e0-a7b8-515ee2dc97fa"></td>
<td>Game Over
<ul>
<li>You can view Your Score</li>
<li>You can view Best Score</li>
<li>Press Enter to start game</li>
</ul>
</td>
</tr>
</table>
</ol>
<hr style="background-color: #4b4c60"></hr>
 <a id="structure"> </a>

## <img align= center width=60px height=60px src="https://media1.giphy.com/media/igsIZv3VwIIlRIpq5G/giphy.gif?cid=ecf05e47faatmwdhcst7c2d4eontr459hjd35zf3an324elo&rid=giphy.gif&ct=s"> File Structure 
<br>
<div align= center>
<img   src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/97bd1f07-1cae-4d27-9366-4e4624015c96">
</div>
<hr style="background-color: #4b4c60"></hr>
<a id ="video"></a>

## <img  align= center width= 70px height =70px src="https://img.genial.ly/5f91608064ad990c6ee12237/bd7195a3-a8bb-494b-8a6d-af48dd4deb4b.gif?genial&1643587200063"> Demo

<div  align="center">
  <img align="center" height=370px  src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/5b26b27b-59fb-4e5d-be19-877a0a832864">
</div>

<hr style="background-color: #4b4c60"></hr>
<a id ="contributors"></a>

## <img  align="center" width= 70px height =55px src="https://media0.giphy.com/media/Xy702eMOiGGPzk4Zkd/giphy.gif?cid=ecf05e475vmf48k83bvzye3w2m2xl03iyem3tkuw2krpkb7k&rid=giphy.gif&ct=s"> Contributors 

<table align="center" >
  <tr>
      <td align="center"><a href="https://github.com/BasmaElhoseny01"><img src="https://avatars.githubusercontent.com/u/72309546?v=4" width="150px;" alt=""/><br /><sub><b>Basma Elhoseny</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/AhmedHosny2024"><img src="https://avatars.githubusercontent.com/u/76389601?v=4" width="150px;" alt=""/><br /><sub><b>Ahmed Hosny</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/nouralmulhem"><img src="https://avatars.githubusercontent.com/u/76218033?v=4" width="150px;" alt=""/><br /><sub><b>Nour Ziad Almulhem</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/EslamAsHhraf"><img src="https://avatars.githubusercontent.com/u/71986226?v=4" width="150;" alt=""/><br /><sub><b>Eslam Ashraf</b></sub></a><br /></td>
  </tr>
</table>

## 🔒 License <a id ="license"></a>

>This software is licensed under MIT License, See [License](https://github.com/BasmaElhoseny01/frog-frenzy/blob/main/LICENSE) for more information ©Frogger.
